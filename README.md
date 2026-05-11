# Motor3D

Un motor 3D en C++ diseñado para proyectos **open-world single-player**, construido sobre **DirectX 11** y **PhysX**.  
Este repositorio contiene la base del motor, incluyendo renderizado, física, sistema de entidades y utilidades esenciales.
Es un proyecto grande a largo plazo con muchas expectativas. Es solo un experimento.

---

## 🚀 Características actuales
- **Renderizado** con DirectX 11 (ventana, swap chain, render target, viewport).  
- **Sistema de física** con NVIDIA PhysX (escena con gravedad y dispatcher).  
- **Cámara** con matrices de vista y proyección usando DirectXMath.  
- **InputSystem** para manejo de estados de teclas.  
- **ECS (Entity Component System)** básico para creación y gestión de entidades y componentes.  
- **SceneManager** con soporte inicial para carga y descarga de escenas.  
- **ResourceManager** para gestión de recursos (texturas, modelos, shaders).  
- **Logger** con salida a archivo y timestamps.  

---

## 📦 Instalación

### Requisitos
- **Visual Studio Community 2026**  
- **Windows 10/11**  
- **vcpkg** instalado y configurado  

### Dependencias (definidas en `vcpkg.json`)
- `physx`  
- `directxtk`  
- `directxmath`  

-**recuerda activar manifest mode y enlazar los additional include directories y additional libs si es q no estan ya**

### Pasos
1. Clona el repositorio:
   ```bash
   git clone https://github.com/Zenxxl/OpenWorldEngine.git
   cd OpenWorldEngine
