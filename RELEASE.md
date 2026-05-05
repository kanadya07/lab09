# Release

Для лабораторной работы используется тег:

```text
v0.1.0.0
```

Команды для создания пакета:

```bash
cmake -S . -B _build -DCPACK_GENERATOR="TGZ" -DBUILD_TESTS=OFF
cmake --build _build --target package
```

После сборки архив из `_build` загружается в GitHub Release.
