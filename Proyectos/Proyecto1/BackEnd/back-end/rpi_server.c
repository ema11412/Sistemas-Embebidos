#include <stdio.h> /* perror() */
#include <stdlib.h> /* exit() */
#include <strings.h> /* bzero(), bcmp() */

#include <unistd.h> /* close() */

#include <netdb.h> /* struct sockaddr_in, INADDR_ANY */

#include <stdint.h> /* uintN_t */

#include <string.h> /* strlen() */

#include <gpio.h>
#include <snap.h>

#if !defined(NDEBUG)
#define static_assert(CONDITION, MSG) { typedef char test[(CONDITION) ? 1 : -1]; (void)(test*) #MSG; } ((void)0)
#endif /* DEBUG compile time assert */

/* some global variables for the socket server */
#define BUFSIZE_TOTAL (256U)
#define PORT (5001)
#define CONCURRENT_CLIENTS (1)

#define ALL_LIGHTS (10)

#if !defined(NDEBUG)
char const device[] = "gpiochip0";
#else /* Release value */
char const device[] = "/dev/gpiochip0";
#endif /* Debug / Release value */

int const light_pins[5] = {
  9,  /* PIN 21 */
  10, /* PIN 19 */
  17, /* PIN 11 */
  22, /* PIN 15 */
  27  /* PIN 13 */
};
int const door_pins[4] = {
  6,  /* PIN 31 */
  13, /* PIN 33 */
  19, /* PIN 35 */
  26  /* PIN 37 */
};

typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr sockaddr;

enum { USE_THE_OPTION = 1 };

typedef enum
{
  PIN_OFF = 0,
  PIN_ON = 1
} PIN_VALUE;

typedef struct
{
  unsigned door1: 1;
  unsigned door2: 1;
  unsigned door3: 1;
  unsigned door4: 1;
} door_status_t;

door_status_t
get_door_status( void )
{
  door_status_t status;

  status.door1 = gpio_read(device, door_pins[0]).value;
  status.door2 = gpio_read(device, door_pins[1]).value;
  status.door3 = gpio_read(device, door_pins[2]).value;
  status.door4 = gpio_read(device, door_pins[3]).value;

  return status;
}

void
turn_light_on( int const light )
{
  gpio_write(device, light_pins[light - 1], PIN_ON);
}

void
turn_light_off( int const light )
{
  gpio_write(device, light_pins[light - 1], PIN_OFF);
}

void turn_all_lights_on( void )
{
  gpio_write(device, light_pins[0], PIN_ON);
  gpio_write(device, light_pins[1], PIN_ON);
  gpio_write(device, light_pins[2], PIN_ON);
  gpio_write(device, light_pins[3], PIN_ON);
  gpio_write(device, light_pins[4], PIN_ON);
}

void
turn_all_lights_off( void )
{
  gpio_write(device, light_pins[0], PIN_OFF);
  gpio_write(device, light_pins[1], PIN_OFF);
  gpio_write(device, light_pins[2], PIN_OFF);
  gpio_write(device, light_pins[3], PIN_OFF);
  gpio_write(device, light_pins[4], PIN_OFF);
}

static void
init_sockaddr_in(sockaddr_in* s, uint16_t portno)
{
  s->sin_family = AF_INET;
  s->sin_addr.s_addr = INADDR_ANY;
  s->sin_port = htons(portno);
}

void
rpi_server( void )
{
  int sockfd;
  uint16_t const portno = PORT;
  char buffer[BUFSIZE_TOTAL] = {0};
  sockaddr_in serv_addr;
  sockaddr_in cli_addr;
  uint32_t clilen = sizeof(cli_addr); /* MUST be of the same size as int, per BSD sockets */
  int option_flag = USE_THE_OPTION;
  int setopt;

  char const quit[] = "quit";

  char const door_status[] = "ds";
  char const light_on[] = "lon";
  char const light_off[] = "loff";
  char const photo[] = "foto";
  char const snap_fail[] = "F";

  char error[] = "error: invalid msg";

  #if !defined(NDEBUG)
  static_assert(sizeof(int) == sizeof(clilen), "int and uint32_t are NOT the same size");
  #endif /* DEBUG compile time assert */

  /* Initialize socket structure */
  bzero((char *) &serv_addr, sizeof(serv_addr));

  /* create socket and get file descriptor */
  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  init_sockaddr_in(&serv_addr, portno);

  /* option to reuse the port assigned */
  setopt = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &option_flag, sizeof(option_flag));

  if ( setopt < 0 )
  {
      perror("set reuse port option");
      exit(1);
  }

  /* bind the host address using bind() call */
  if ( bind(sockfd, (sockaddr *)&serv_addr, sizeof(serv_addr)) < 0 )
  {
    perror("ERROR on binding\n");
    exit(1);
  }

  /* start listening for the clients, */
  /* here process will go in sleep mode and will wait for the incoming connection */
  listen (sockfd, CONCURRENT_CLIENTS);

  for(;;)
  {
    /* accept actual connection from the client */
    int newsockfd = accept (sockfd, (sockaddr *)&cli_addr, &clilen);
    if ( read (newsockfd, buffer, sizeof(buffer) - 1) < 0 )
    {
      perror("ERROR in reading from socket");
      exit(1);
    }

    if ( bcmp(buffer, quit, sizeof(quit) - 1) == 0 )
    {
      if (write(newsockfd, quit, sizeof(quit)) < 0)
      {
        perror("error in writing \"quit\" to socket");
      }
      break;
    }
    else if ( bcmp(buffer, door_status, sizeof(door_status) - 1) == 0 )
    {
      door_status_t const _result = get_door_status();
      char result[4];
      result[0] = _result.door1 ? '1' : '0';
      result[1] = _result.door2 ? '1' : '0';
      result[2] = _result.door3 ? '1' : '0';
      result[3] = _result.door4 ? '1' : '0';

      if (write(newsockfd, result, sizeof(result)) < 0)
      {
        perror("error in writing \"ds\" to socket");
      }
    }
    else if ( bcmp(buffer, light_on, sizeof(light_on) - 1) == 0 )
    {
      int const light = atoi(&buffer[sizeof(light_on) - 1]);
      if (light == ALL_LIGHTS)
      {
        turn_all_lights_on();
      }
      else
      {
        turn_light_on (light);
      }
      if (write(newsockfd, light_on, sizeof(light_on))  < 0)
      {
        perror("error in writing \"lon\" to socket");
      }
    }
    else if ( bcmp(buffer, light_off, sizeof(light_off) - 1) == 0 )
    {
      int const light = atoi(&buffer[sizeof(light_off) - 1]);
      if (light == ALL_LIGHTS)
      {
        turn_all_lights_off();
      }
      else
      {
        turn_light_off (light);
      }
      if (write(newsockfd, light_off, sizeof(light_off)) < 0)
      {
        perror("error in writing \"loff\" to socket");
      }
    }
    else if ( bcmp(buffer, photo, sizeof(photo) - 1) == 0 )
    {
      char const* const result = ( snap() ) ? snap_frame_path : snap_fail;
      if (write(newsockfd, result, strlen(result)) < 0)
      {
        perror("error in writing to \"foto\" socket");
      }
    }
    else
    {
      if (write(newsockfd, error, sizeof(error)) < 0)
      {
        perror("error in writing \"error\" to socket");
      }
    }

    /* cleanup buffer */
    bzero(buffer, sizeof(buffer));
    close(newsockfd);
  }
  close(sockfd);
}
