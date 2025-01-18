# SolenoidTrigger5V UNIT

<img src="https://github.com/akita11/SolenoidTrigger5V_UNIT/blob/main/https://github.com/akita11/SolenoidTrigger5VUNIT.jpg" width="240px">

5V電源のみで[タカハのスリムロック](https://www.takaha.co.jp/co/product-slim-lock/)など12V程度以上の高い電圧が必要な負荷を、コンデンサに蓄積したエネルギーで短時間駆動できるユニットです。駆動後は、繰り返しエネルギーを充電して駆動することができます。なおスリムロックの開閉状態をGrove端子から計測するための接続端子もあります。


## 使い方（接続方法）

<img src="https://github.com/akita11/SolenoidTrigger5V_UNIT/blob/main/https://github.com/akita11/SolenoidTrigger5VUNIT_wiring.jpg" width="240px">

オレンジの端子に、以下のように負荷を接続します。
- スリムロックのソレノイド（白ワイヤ）: 基板裏面"SOL"側（極性なし）
- スリムロックの開閉センサ（赤ワイヤ）: 基板裏面"ST"側（極性なし）

Grove端子にはM5Stack等のマイコンに接続します。


## 使い方（ソフトウエア）

Grove端子のp1（コネクタの端側）を駆動信号TRGを"1"にすると、コンデンサに蓄積したエネルギーでスリムロックなどの負荷を一瞬だけ駆動します（施錠状態のスリムロックが解錠されます）。

Grove端子のp2（コネクタのVDD側）は、ST端子がショート時には"0"、オープン時には"1"となり、Grove端子に接続したM5Stack等のマイコンから読み取ることができます。（内部プルアップ）

なお後述の動作モードに応じて、"1"にしてから負荷が駆動されるまでに数秒程度時間がかかる場合があります。また充電動作中はオレンジLEDが点灯し、その間は負荷の駆動が行われません。


## 動作モードの設定

<img src="https://github.com/akita11/SolenoidTrigger5V_UNIT/blob/main/https://github.com/akita11/SolenoidTrigger5VUNIT_jumper.jpg" width="240px">

基板裏面のJP1によって、動作モードを切り替えることができます。必要に応じて半田を盛ってショートさせてください。

### JP1=オープン時（初期状態）

本ユニットの通電中は、常時コンデンサにエネルギーが蓄積された状態が保たれ、駆動信号TRGを"1"にすると、ほぼ即時に負荷が駆動されます。
非駆動時でもコンデンサのエネルギーは徐々に減少するため、適宜、自動的に充電動作（オレンジLEDが点灯）が行われ、その期間はTRGを"1"にしても負荷は駆動されません。
待機時にもエネルギー蓄積が行われるため、消費電力ははや増えますが、即時に負荷を駆動できます。


### JP1=ショート時

コンデンサのエネルギー蓄積が、駆動信号TRGを"1"にしてから行い、エネルギー蓄積後に負荷が駆動されます。そのため、TRGを"1"にしてから数秒後に負荷が駆動されます。待機にはエネルギーの蓄積が行われないため、低消費電力動作に向いています。


## Author

Junichi Akita (@akita11) / akita@ifdl.jp
