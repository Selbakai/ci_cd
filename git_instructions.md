# Instrucciones para subir al repositorio GitHub con token

## Paso 1: Obtener tu token personal de GitHub
1. Ve a GitHub.com → Settings → Developer settings → Personal access tokens → Tokens (classic)
2. Genera un nuevo token con permisos de "repo"
3. Copia el token generado

## Paso 2: Configurar Git con el token
Ejecuta este comando reemplazando TU_TOKEN_AQUI con tu token real:

```cmd
git remote set-url origin https://TU_TOKEN_AQUI@github.com/Selbakai/ci_cd.git
```

## Paso 3: Subir los cambios
```cmd
git push -u origin main
```

## Alternativa: Usar Git Credential Manager
También puedes usar:
```cmd
git config --global credential.helper manager-core
git push -u origin main
```
Y cuando te pida credenciales, usa:
- Username: Selbakai
- Password: tu_token_personal

## Verificar el upload
Después del push exitoso, verifica en: https://github.com/Selbakai/ci_cd.git

## Archivos incluidos en este commit:
- main.c (programa principal)
- main.h (archivo de cabeceras)
- README.md (documentación)
- .gitignore (archivos a ignorar)
- git_instructions.md (este archivo)
