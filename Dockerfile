# We only do 3DS at the moment
FROM devkitpro/devkitarm:latest

WORKDIR /project
CMD cmake -DCMAKE_TOOLCHAIN_FILE=$DEVKITPRO/cmake/3DS.cmake -B build
WORKDIR /project/build
CMD make -j${nproc}
