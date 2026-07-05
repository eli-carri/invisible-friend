# Invisible Friend — Amigo Invisible con Bipartite Matching

Mini-proyecto para organizar el "amigo invisible" (Secret Santa) entre un grupo de amigos, usando el algoritmo de **Ford-Fulkerson** para resolver el problema como un **matching bipartito**: cada persona debe quedar asignada a otra persona distinta a sí misma para regalarle algo, garantizando que la asignación sea válida (nadie se regala a sí mismo) y completa.

Una vez calculadas las asignaciones, el programa envía por mail a cada participante quién le tocó, sin que el resto del grupo pueda verlo.

## ¿Cómo funciona?

1. Se pide por consola la cantidad de jugadores.
2. Se crea una partida (`Game`) y se cargan los datos de cada amigo (`Friend`): nombre y mail, presumiblemente.
3. Se ejecuta el matching bipartito (implementado con Ford-Fulkerson) para asignar a cada persona un destinatario válido de regalo.
4. Se envían los emails de forma automática informando a cada uno su asignación.

## Estructura del repositorio

| Archivo / carpeta | Descripción |
|---|---|
| `__main__.py` | Punto de entrada del programa. Pide el número de jugadores, arma la partida, corre el algoritmo de asignación y dispara el envío de mails. |
| `classes/` | Módulos con la lógica principal: la clase `Friend` (representa a cada participante) y la clase `Game` (orquesta la carga de amigos, el matching y el envío de emails). |
| `bipartite-matching.cpp` | Implementación en C++ del algoritmo de matching bipartito (Ford-Fulkerson) usado para calcular las asignaciones. |
| `allocate.exe` | Ejecutable compilado de `bipartite-matching.cpp`, invocado desde Python (vía `subprocess`) para resolver el matching. |
| `requeriments.txt` | Dependencias de Python del proyecto. |

## Requisitos

- Python 3.10+ (recomendado)
- Windows, o un entorno compatible con la ejecución de `allocate.exe` (o bien recompilar `bipartite-matching.cpp` para tu sistema operativo si no usás Windows)
- Una **cuenta de Google** con una **contraseña de aplicación (App Password)** generada, para poder enviar los mails con las asignaciones.
- Dependencias listadas en `requeriments.txt`:
  - `numpy==2.2.3`
  - `pandas==2.2.3`
  - `python-dateutil==2.9.0.post0`
  - `pytz==2025.1`
  - `six==1.17.0`
  - `tzdata==2025.1`

## Instalación

```bash
git clone https://github.com/eli-carri/invisible-friend.git
cd invisible-friend
pip install -r requeriments.txt
```

## Configuración de Google (envío de mails)

Para que el programa pueda enviar los emails con las asignaciones, necesitás:

1. Tener activada la **verificación en dos pasos** en tu cuenta de Google.
2. Generar una **contraseña de aplicación** desde la configuración de seguridad de tu cuenta de Google (`myaccount.google.com` → Seguridad → Contraseñas de aplicaciones).
3. Usar esa contraseña de aplicación (no tu contraseña habitual) en la configuración de envío de correo del proyecto.

## Uso

Desde la raíz del proyecto:

```bash
python __main__.py
```

El programa va a pedirte:

```
Number of players: 
```

A partir de ahí:
1. Se cargan los datos de cada participante.
2. Se corre el matching bipartito para definir quién le regala a quién.
3. Se envían automáticamente los mails de notificación.
4. Al finalizar, vas a ver el mensaje `Thank you for playing <3`.

## Notas

- El algoritmo garantiza que ninguna persona quede asignada a sí misma.
- Las asignaciones no se muestran en la consola ni quedan expuestas: cada participante se entera únicamente por su propio email.
- Si no usás Windows, es posible que necesites recompilar `bipartite-matching.cpp` para generar un ejecutable compatible con tu sistema operativo, en lugar de usar `allocate.exe`.
- El proyecto usa Ford-Fulkerson porque el problema de asignación (cada persona da y recibe un solo regalo) puede modelarse como un flujo máximo en un grafo bipartito, donde el matching máximo resultante es la asignación buscada.
