# Output

```
Output
+ RootNtuple
+ TxtNtuple
```

RootNtuple - сохранить результаты в формате root.
TxtNtuple - сохранить результаты в формате txt.
Можно выбрать оба, как реализовано выше.

# Reverse
Два варианта:
```
Reverse false
```
и
```
Reverse true
```

Когда Reverse true - значения qShort, qLong и baseline умножаются на -1.

# DataPSD
```
DataPSD
+ qShort
+ qLong
+ cfd_y1
+ cfd_y2
+ baseline
+ height
+ eventCounter
+ eventCounterPSD
+ psdValue
```

Перечень всех параметров, которые находятся в бинарном файле. Обязательно все, иначе работать программа будет неверно.

# DataWaveform
```
DataWaveform
+ qShort
+ qLong
+ baseline
+ entries
```

qShort, qLong - интегралы
baseline - шум
entries - запись сигнала в отдельный ntuple по каждому моменту снятия данных (не по событиям, а каждая точка из сигнала для всех событий)

# WaveformConfig
```
WaveformConfig
+ baseline 100
+ qShort 120
+ qLong 380
+ wavelength 1000
```

# Histogram
```
Histrogram
+ PSD qShort 1000 -20000 200000
```
Структура:
Тип файла - Параметр - Количество бинов - минимальное значение - максимальное значение.
Тип файла может быть: PSD или Waveform.
