# bp-monitor
Modelling of Blood Pressure monitor in Proteus (bachelor thesis)


### Schematics
![sch](https://github.com/iam28th/bp-monitor/blob/master/img/Schematics.jpg)
 
Содержательная часть схемы слева-направо:
 1. Блок PRESSURE SENSOR & PUMP содержит ЦАП и микроконтроллер, который программно задаёт выходной сигнал блока, аналогичный сигналу датчика давления.
 2. ФВЧ 2 порядка с частотой среза 0.5ГЦ для выделения осцилляций.
 3. Делитель напряжения (чтобы сделать осцилляции положительными).
 4. Суммирующий усилитель.

Также реализованы вывод данных на дисплей и запись на SD карту по SPI*.

\*В настоящий момент накладка: Proteus не очень хорошо вывозит моделирование. То есть в этой схеме команда записи на карточку возвращает ошибки (каждый раз разные!) и исправно работает где-то 1 из 8 раз. Если же собрать проект только из МК с карточкой, то с той же самой прошивкой всё работает стабильно.

Поскольку Proteus похоже себя исчерпал, алгоритм определения непосредственно СД и ДД думаю реализовывать в питоне. 

### Results

Сигнал с "датчика" следующий:

#### Давление в манжете:
![cuff](https://github.com/iam28th/bp-monitor/blob/master/img/PlotCuffPressure.jpg)

#### Осцилляции:
![osc](https://github.com/iam28th/bp-monitor/blob/master/img/PlotOscillations.jpg)

Реализация амплитудного метода определения АД:
![ampl](https://github.com/iam28th/bp-monitor/blob/master/img/amplitude_method.jpg)

### References

https://www.researchgate.net/project/Database-of-raw-data-from-blood-pressure-cuff - отсюда брал данные для моделирования датчика давления.
