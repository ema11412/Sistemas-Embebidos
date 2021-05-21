# Taller 7

control de GPIO en raspberry pi 2 + yocto

## integrantes

- David Cordero Chavarría
- Emanuel Esquivel Lopez
- Ricardo Valverde Hernández

## importante

Desde la versión 4.8 de Linux, el GPIO se accede mediante un character device en `/dev/gpiochip0`, no mediante sysfs (`/sys/class/gpio/export`, `/sys/class/gpio/unexport`, etc.)

## Respuestas a las preguntas del enunciado

### 3.6

Al compiler con el toolchain el programa, el ejecutable `sayhello` no se puede ejecutar en la computadora donde se compiló, porque este ejecutable fue generado para una arquitectura ARM, a menos que la computadora en que se generó tenga arquitectura ARM, el formato del ejecutable no puede ser ejecutado en esa computadora normalmente, aunque es posible usar qemu y algunas configuraciones para 'esconder' esto, y lograr ejecutar algunos tipos de ejecutables a través de una capa de emulación, esto requiere configuración especial, y no es el comportamiento por defecto,

### 3.9

Pero al intentar ejecutarlo en la raspberry pi, sí debería poder ser ejecutado, y mostrar el mensaje `Hello, World`

### 4.1.1

Antes del cambio en la interfaz proveida por el kernel (mencionado en `importante` arriba), se debía escribir el número BCM del pin por usar a sysfs, ahora, se debe usar el character device.


### 4.1.2

Antes de el cambio en la interfaz proveida por el kernel, se podía simplemente escribir texto a un archivo virtual, por ejemplo para un pin especifico se debe escribir en `value` creado cuando se exporta el pin, esto mediante el comando
 ```# echo "value" > /sys/class/gpio/gpio#pin/value```
 Donde `#pin` representa el pin a escribir y `value` el valor deseado, ya sea `0` o `1`.

 Ahora se debe usar un programa en C, aunque de igual manera este no requiere permisos de superusuario
