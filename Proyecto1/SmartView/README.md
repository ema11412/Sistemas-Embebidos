## Run it

```
cd server
npm install
npm start
```
_Basic conect to server_

El ```localhost:8080/test``` simula las interacciones con las puertas y muetra los mensajes enviados.


## Uso

Acceder ```localhost:8080/local```



```
User : Nero
Pass : yep
```

Utilizar los botones para encender y apagar luces.

Si se envian datos de las puertas estas seran reflejadas de inmediato al ser enviadas al servidor.


### Camara

En la parte derecha de la vista webapp tenemos el boton de captura, es para enviar al servidor ```foto```, esto lo que hace es devolver la ruta de la imagen. 

Por defecto es ```app/cap```