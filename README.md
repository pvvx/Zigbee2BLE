# Zigbee2BLE
Gateway Zigbee in BLE on modules with TLSR825x.


Первая тестовая версия.

Текущая версия пока работает с такими Zigbee датчиками:  [z03mmc](https://github.com/pvvx/z03mmc), [ts0201](https://pvvx.github.io/TS0201_TZ3000), Aqura (LUMI.weater)

Используется TB-03F-kit. Он будет являться координатором в сети Zigbee и BLE устройством, перетранслирующим данные с Zigbee в BLE рекламу в формате BTHome v2.

**Подготовка**

1. Прошить файл [zb2ble.bin](https://github.com/pvvx/Zigbee2BLE/raw/master/out/zb2ble.bin) с помощью TlsrComProg.py в TB-03F-kit, соединив 2 ногу чипа USB-COM с SWS:

![TB-03F-KIT-PGM.gif](https://github.com/pvvx/Zigbee2BLE/blob/master/img/TB-03F-KIT-PGM.gif)

```
python3 TlsrComProg.py -pCOM10 -u we 0 out\zb2ble.bin
```

После прошивки запустить модуль TB-03F-kit, нажав кнопку "rst" на нем.

2. Запустить [Zigbee2ble.html](https://pvvx.github.io/Zigbee2ble/Zigbee2ble.html). 

3. Соединиться с `z2b_xxxxxx` BLE устройством.

4. Только при первом старте прошивки, на странице "Zigbee2ble" выбрать кнопку 'Start network'. Соединение может разорваться - тогда заново пересоединиться с устройством.

На этом система готова для регистрации Zigbee датчиков.

**Подключение Zigbee устройства**

1.	Соединиться с `z2b_xxxxxx` BLE устройством в [Zigbee2ble.html](https://pvvx.github.io/Zigbee2ble/Zigbee2ble.html).
2.	Выставить галку “Auto Joinng”.
3.	На подключаемом Zigbee устройстве нажать кнопку для регистрации, а на странице "Zigbee2ble" - "Permit join 250 sec" или кнопку "prog" на TB-03F-kit.
4.	Дождаться регистрации устройства - в таблице будут указаны имя устройства и binding кластеры. Для ts0201 может не быть списка кластеров, но данные по температуре, влажности и батареи появится спустя некоторое время.
5.	Отключиться от `z2b_xxxxxx` BLE устройства и настроить прием BLE рекламы в интеграции “BTHome” в “Home Assistant” или в другой системе...


![Zigbee2ble.png](https://github.com/pvvx/Zigbee2BLE/blob/master/img/Zigbee2ble.png?raw=true)


Пример приема замеров от z03mmc через Zigbee2BLE в “Home Assistant”:

![z03mmc.png](https://github.com/pvvx/Zigbee2BLE/blob/master/img/z03mmc.png?raw=true)

