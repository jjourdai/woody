make;

./woody_woodpacker -c xor32 $1 && ./woody
./woody_woodpacker -c xor16 $1 && ./woody
./woody_woodpacker -c xor8 $1 && ./woody
