# Magma Encryptor

Реализация шифрования "Магма" (ГОСТ 34.12-2018) в режиме ECB с анализом производительности.

## Зависимости
Установите на Ubuntu:
```bash
sudo apt update
sudo apt install cmake g++ make
```

## Сборка
```bash
git clone https://github.com/Butters7/magma-gost-34-12-2018.git
cd magma-gost-34-12-2018
mkdir build
cd build
cmake . .
make
./test/magma-test 'входной файл' 'выходной файл'
```

Файлы можно поместить в проект в папку files
```bash
cd magma-gost-34-12-2018
mkdir files
mv .. ./files
```
