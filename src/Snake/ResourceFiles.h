#pragma once

#define RES_PATH "../../res"//vuelve atras 2 veces y entra a la carpeta res
#define RESOURCE_FILE(name) (RESOURCE_PATH+(name)).c_str() //recibe un nombre, le agrega "../../" delante y lo convierte en un array de chars acabado en null character (\0) (C-String)
