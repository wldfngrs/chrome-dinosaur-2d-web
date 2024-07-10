# Dino Saur (Web)

A 2D colorful reimagining of the chrome dinosaur offline game for the web.

Play the game right here: https://wldfngrs.itch.io/dino-saur

## Installing, Compiling

Download and install [emscripten](https://emscripten.org/docs/getting_started/downloads.html) and execute the following command in the project's root directory:

```
$ em++ -o index.html BackgroundSprite.cpp Collision.cpp DinoSprite.cpp DirtManager.cpp Game.cpp Main.cpp ObstacleManager.cpp ObstacleSprite.cpp Score.cpp SoundManager.cpp SpriteComponent.cpp Text.cpp TextureManager.cpp Vector2D.cpp -sUSE_SDL=2 -sUSE_SDL_IMAGE=2 -sUSE_SDL_TTF=2 -sUSE_SDL_MIXER=2 -sSDL2_IMAGE_FORMATS=['png'] -sUSE_GLFW=3 -sWASM=1 -sASYNCIFY -s GL_ENABLE_GET_PROC_ADDRESS=1 --preload-file Assets
```

The compiled ``.js``, ``.wasm``, ``.data``, and ``.html`` files are located in the project's root.

## Contributing

Pull requests are welcome! For major refactors, please open an issue first to discuss what you would like to improve. Feel free to create a fork of this repository or use the code for any other noncommercial purposes.
