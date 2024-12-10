cd lisc32_isn
make
cd ..
cd lisc32_emu
make
cd ..
cd lisc32_asm
make
cd ..

cp build/isn/liblisc32_isn.so  build/liblisc32_isn.so
cp build/asm/lisc32_asm build/lisc32_asm
cp build/emu/lisc32_emu build/lisc32_emu
