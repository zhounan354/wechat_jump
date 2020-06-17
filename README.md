# wechat_jump
wechat_jumpgame,autojump
微信跳一跳小程序游戏的自动游戏工具

## 使用说明

### 首先
你得用你的电脑控制手机，不管用什么方法。
airplay也好，Android模拟器也好，只有有图像可以显示出来，鼠标点击可以代替触屏按键，就可以使用此工具进行游戏。

本人手机越狱，使用airplay可以直接操作手机。
没越狱的推荐用Android模拟器登录微信玩。

### 按键说明

打开程序后，运行图片如下

![初始图片](http://m.qpic.cn/psb?/V12HOrsc4bYHVW/i4mrRaX9clhH3Ld6FzFm3oHD2e94UwsPOB58jhEtqTU!/b/dPIAAAAAAAAA&bo=gwM0AgAAAAADB5Q!&rf=viewer_4)


* 调试键

上面三个窗口，分别是 我在这、要去这、图像，用于调试时使用，我在这，就是跳一跳的主角位置，要去这就不说了，图像是用于获取位置的图像，这三个窗口都可以通过右下角的调试按钮关闭，再按一次开启。

* 设置窗口

我以图片代替控制器，作简单说明
点击  开始  按键后，开始采集桌面图像，如下图

![未调整](http://m.qpic.cn/psb?/V12HOrsc4bYHVW/t1heHhSKwlyf7tA845*k1S3dK7IqJDQ1qEwSTVx1OEE!/b/dPIAAAAAAAAA&bo=0gSAAgAAAAADB3Y!&rf=viewer_4)

可以看到，图像 窗口已经截取了图片，并且处理后显示在了 我在这 和 要去这 两个图像里，从图像窗口可以看出，截取的图像里面，还有边框，调整边框的四个值，让截取的图像不带边框。左边两个是左上角的xy值，右边两个是右下角的xy值，x值从左到右增大，y值从上往下增大，也就是说（0,0）是屏幕最左上角，（1080,980）是屏幕右下角，修改这四个值，修改完毕后点击  设置窗口  按钮，使修改生效，观察 图像 窗口是否正确显示。

![最终结果](http://m.qpic.cn/psb?/V12HOrsc4bYHVW/GlS29edeJXYX0h4vdYRiLlLEUJjuC1D6*GLNCpMmbj0!/b/dPMAAAAAAAAA&bo=wQSAAgAAAAADN1U!&rf=viewer_4)

* 设置阈值

设置阈值的时候，点击加号或减号按钮，阈值大小是否合适，以能正常显示 我在这 为标准，并且，颜色比较深的箱子的影子，不会出现在 我在这 里面（我在这 图像里，出现一条黑色竖线，穿过我的位置，说明能正确找到）
加号和减号点击一次，会以步长为单位加减

* 设置距离

基本可以开始玩了
跳的不够远？没问题，把距离设置大一点，太远就把距离设置小一点

* 设置速度

就是跳一次之后休息的时间
之所以要休息，要留时间给图像采集，刚跳完的时候前方盒子未到位，目标识别不准确，单位是0.1s，亲测26比较合适，但如果有些方块有加分，弹出来的数字，可能会影响目标方块的识别。

## 说明完毕，可以开始上1000分了

## 原理说明
用opencv库识别了i的位置，和目标方块出现的位置，只要找到横坐标就可以了，设横坐标差值是dx，按压时间是y，y=k\*dx,目标就是找到k值，该工具把k值的寻找，交给使用者自行寻找了，反正找起来也快，避免了不同玩家计算方法不一样，增加了通用性。
想了解具体原理的，可以直接看源码。
