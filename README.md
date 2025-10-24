# Pinewood-Derby-EDF-Car
Pinewood Derby EDF Car - 3D Printed - No Rules Class

This is a remix of the ducted fan derby car posted by NegativeC [here](https://github.com/NegativeC/ducted-fan-pinewood-derby).

I also designed the car similar to Christopher-72 from the issues thread on that project. [Go give those a look](https://github.com/NegativeC/ducted-fan-pinewood-derby/issues/2) for ideas as well.

This project uses an EDF 3S jet fan to propel the car. The entire car is 3d printed allowing for space for the battery, ESC, and arduino trinket, IR sensors, and wiring. 

When the IR sensors are blocked with the starting pin, the car goes into staging mode. When the pin drops, the car goes into racing mode at full speed for 1.5 seconds. After this time it will not go back to staging mode until the arduino has been reset for safety. Mine went 35 ft in 1.6 seconds. 15 MPH. 

650 mah 3S Lipo Battery - $12 - [Lipo Battery](https://www.aliexpress.us/item/3256809691650091.html?spm=a2g0o.detail.similar_items.1.1b672tJO2tJO5e&utparam-url=scene%3Aimage_search%7Cquery_from%3Adetail_bigimg%7Cx_object_id%3A1005009877964843%7C_p_origin_prod%3A&algo_pvid=70498a28-a5d0-41b9-a6cc-3642210f86f0&algo_exp_id=70498a28-a5d0-41b9-a6cc-3642210f86f0&pdp_ext_f=%7B%22order%22%3A%22-1%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21USD%2112.95%2112.95%21%21%2112.95%2112.95%21%40210311a017612786087098837e6bb2%2112000050454996079%21sea%21US%212000527519%21ACX%211%210%21n_tag%3A-29919%3Bd%3Ae7d49904%3Bm03_new_user%3A-29894&gatewayAdapt=4itemAdapt)

Hobbywing Skywalker ESC - $10 - [Hobbywing ESC](https://www.aliexpress.us/item/2251832468941883.html?spm=a2g0o.order_list.order_list_main.39.1fea1802QtOHtJ&gatewayAdapt=glo2usa)

XFly 40mm EDF Ducted Fan - $25 - [XFly Fan](https://www.amazon.com/dp/B0BXPLYJTX?ref=ppx_yo2ov_dt_b_fed_asin_title)

IR Break Sensors - $9 - [IR Sensors](https://www.amazon.com/dp/B09V76Z4CB?ref=ppx_yo2ov_dt_b_fed_asin_title&th=1)

Adafruit Trinket - $11 - [Trinket](https://www.amazon.com/dp/B00K9THV04?ref=ppx_yo2ov_dt_b_fed_asin_title)

## Library Dependencies
Adafruit SoftServo - https://github.com/adafruit/Adafruit_SoftServo
