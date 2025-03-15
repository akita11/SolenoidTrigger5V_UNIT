# SolenoidTrigger5V UNIT

<img src="https://github.com/akita11/SolenoidTrigger5V_UNIT/blob/main/SolenoidTrigger5VUNIT-1.jpg" width="240px">

<img src="https://github.com/akita11/SolenoidTrigger5V_UNIT/blob/main/SolenoidTrigger5VUNIT-2.jpg" width="240px">

<img src="https://github.com/akita11/SolenoidTrigger5V_UNIT/blob/main/SolenoidTrigger5VUNIT.jpg" width="240px">

5V電源のみで[タカハのスリムロック](https://www.takaha.co.jp/co/product-slim-lock/)など12V程度以上の高い電圧が必要な負荷を、コンデンサに蓄積したエネルギーで短時間駆動できるユニットです。駆動後は、繰り返しエネルギーを充電して駆動することができます。なおスリムロックの開閉状態をGrove端子から計測するための接続端子もあります。


## 使い方（接続方法）

<img src="https://github.com/akita11/SolenoidTrigger5V_UNIT/blob/main/SolenoidTrigger5VUNIT_wiring1.jpg" width="240px">

<img src="https://github.com/akita11/SolenoidTrigger5V_UNIT/blob/main/SolenoidTrigger5VUNIT_wiring2.jpg" width="240px">

オレンジの端子に、以下のように負荷を接続します。
- スリムロックのソレノイド（白ワイヤ）: 基板裏面"SOL"側（極性なし）
- スリムロックの開閉センサ（赤ワイヤ）: 基板裏面"ST"側（極性なし）

Grove端子にはM5Stack等のマイコンに接続します。


## 使い方（ソフトウエア）

Grove端子のp1（コネクタの端側）を駆動信号TRGを"1"にすると、コンデンサに蓄積したエネルギーでスリムロックなどの負荷を一瞬だけ駆動します（施錠状態のスリムロックが解錠されます）。
なお"1"にしてから負荷が駆動されるまでに0.5秒程度時間がかかります。充電動作中はオレンジLEDが点灯し、その間は負荷の駆動が行われません。

Grove端子のp2（コネクタのVDD側）は、ST端子がショート時には"0"、オープン時には"1"となり、Grove端子に接続したM5Stack等のマイコンから読み取ることができます。（内部プルアップ）


### UIFlow(v1)用のカスタムブロック

<img src="https://github.com/akita11/SolenoidTrigger5V_UNIT/blob/main/SolenoidTrigger5VUNIT-1.jpg" width="240px">

UIFlow(v1)で、Customから"SolenoidTrigger5V.m5b"を読み込むと、"SolenoidTrigger5VUnit"内の3つのブロックが使えるようになります。

- Init : 解除信号(Groveのp1端子:CtrlPin)とST端子状態(Groveのp2端子:StatusPin)のピン番号を指定します。最初に1回だけ実行します。例：Core2のPortAはp1=GPIO33、p2=GPIO32なので、この図のように指定します。その他の機種・ポートのピン番号は仕様を確認してください。
- Unlock : ロック解除を行います
- Status : ST端子の状態を取得します。スリムロックの場合は、解錠時に"1"、施錠時に"0"になります。


## Author

Junichi Akita (@akita11) / akita@ifdl.jp
