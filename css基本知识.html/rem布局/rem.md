####什么是rem
* 什么是em  
em作为font-size的单位时，代表的是父元素字体的大小，em作为其他属性的单位时，代表自身字体的大小。

缺点：旦某个节点的字体大小发生变化，那么其后代元素都得重新计算
* rem
rem作用于非根元素时，相对于根元素字体大小；rem作用于根元素字体大小时，相对于其出初始字体大小
* 浏览器有默认的最小字体（chrome浏览器最小字体大小为12px）

#### 物理像素和逻辑像素
* 物理像素是设备的屏幕像素，在同一个设备上，它的物理像素是固定的。
* 逻辑像素即css像素
viewport中的一个小方格，CSS样式代码中使用的是逻辑像素。如果在一个设备中，物理像素与逻辑像素相等，将不会产生任何问题。但是，在iphone 4中，物理像素是640px*960px，而逻辑像素数为320*480px。因此，需要使用大约4个物理像素来显示一个CSS像素。
* 设备像素比  
设备像素比是指设备像素与css像素之间的比例。当这个比率为1:1时，使用1个设备像素显示1个css像素。当这个比率为2:1时，使用4个设备像素显示1个css像素。当这个比率为3:1，使用9(3*3)个设备像素显示1个css像素。

在javascript中，可以通过window.devicePixelRatio获取到当前设备的dpr。

在css中，可以通过-webkit-device-pixel-ratio，-webkit-min-device-pixel-ratio和 -webkit-max-device-pixel-ratio进行媒体查询，对不同dpr的设备，做一些样式适配(这里只针对webkit内核的浏览器和webview)。

#### 视口（viewport）
移动浏览器中视口分为几种情况:

1. `<metaname="viewport"content=“width=device-width,minimum-scale=1.0,maximum-scale=1.0”/>`中content所设置的视口，称为布局视口，最大值由浏览器厂商规定 ,可以document.documentElement.clientWidth获取其宽度.

2. 而我们看到的浏览器的窗口，网页区域的大小，称为视觉视口，用css像素表示（设备逻辑像素）

#####图片高清问题
理论上，1个位图像素对应于1个物理像素，图片才能得到完美清晰的展示,在普通屏幕下是没有问题的，但是在retina屏幕下就会出现位图像素点不够，从而导致图片模糊的情况。对于dpr=2的retina屏幕而言，1个位图像素对应于4
个物理像素，由于单个位图像素不可以再进一步分割，所以只能就近取色，从而导致图片模糊

* 对于图片高问题，比较好的方案就是两倍图片。200×300(css pixel)img标签，就需要提供400×600的图片  
缺点1.由于下载了2*的图片，造成资源浪费
2.图片由于downsampling（下采样，缩小图片，主要目的有两个：1、使得图像符合显示区域的大小；2、生成对应图像的缩略图）
可以通window.devicePixelRatio获取到当前设备的dpr。
* 最好的方法是：不同的dpr下，加载不同的尺度的图片

##### 1px问题
设计师想要的retina下border: 1px;，其实就是1物理像素宽，对于css而言，可以认为是border: 0.5px;，这是retina下(dpr=2)下能显示的最小单位。并不是所有手机浏览器都能识别border: 0.5px;，ios7以下，android等其他系统里，0.5px会被当成为0px处理。
* 可以通过照常写border-bottom: 1px solid #ddd;，然后通过transform: scaleY(.5)缩小0.5倍来达到0.5px的效果，但是这样hack实在是不够通用(如：圆角等)，写起来也麻烦。
* 对于dpr=2,添加如下的meta标签，设置viewport(scale 0.5)`<meta name="viewport" content="initial-scale=0.5,maximum-scale=0.5, minimum-scale=0.5,user-scalable=no">`这样，页面中的所有的border: 1px都将缩小0.5，从而达到border: 0.5px;的效果  
然而，页面scale，必然会带来一些问题：

1）字体大小会被缩放

2）页面布局会被缩放(如: div的宽高等)
##### rem适配
基于rem的原理，我们要做的就是: 针对不同手机屏幕尺寸和dpr动态的改变根节点html的font-size大小(基准值)。
rem = document.documentElement.clientWidth * dpr / 10

1）乘以dpr，是因为页面有可能为了实现1px border页面会缩放(scale) 1/dpr 倍(如果没有，dpr=1)。

2）除以10，是为了取整，方便计算(理论上可以是任何值)
#### vw和vh
w —— 视口宽度的 1/100；vh —— 视口高度的 1/100

* vw兼容性不如rem好
* 在使用弹性布局时，一般会限制最大宽度，比如在pc端查看我们的页面，此时vw就无法力不从心了，因为除了width有max-width，其他单位都没有，而rem可以通过控制html根元素的font-size最大值，而轻松解决这个问题
