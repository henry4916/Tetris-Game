# Computational-Photography_HW2
# tetris


## 姓名：賴柏霖
## 學號：609410151
## e-mail：609410151@alum.ccu.edu.tw
## 作業環境：Win10 64bit Visual studio 2017
## 編譯器：Visual Studio 2017
## 參考資料：
https://blog.csdn.net/wangxh88/article/details/84219318
https://github.com/linzhi/tetris
https://blog.csdn.net/weixin_30569153/article/details/97128717?ops_request_misc=&request_id=&biz_id=102&utm_term=opengl%20tetris&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-1-97128717.nonecase&spm=1018.2226.3001.4187
https://github.com/TakashiL/OpenGL-Tetris
https://github.com/xhacker/tetris-opengl
https://github.com/AvronGols/tetris-opengl
https://github.com/xhacker/tetris-opengl
https://www.youtube.com/watch?v=-8teaOoZdxA
## 指定作業功能：
	1.建立一個Tetris遊戲的視窗，包含四個要素：
		a.Game board：是你遊戲的主要窗口，大小為10*20，至少可容納200個方塊。(為了和方塊匹配，建議大小為200x400 pixel)
		b.Preview window：預覽窗口顯示下一個，將生成的方塊。
		c.Score display：顯示當前累積分數。(例：消除一排方塊獲得10分，若同時消除越多排分數越高，mark = 10 * Combo * Combo，Combo = number of rows disappeared for a single block)
		d.Level display：指當前難度，控制方塊的下落速度。(例：分數每超過30分，上升難度，加快下落速度，the falling speed equals to [1000msec –(level – 1) * 100] per grid-square)

	2.請將四格骨牌設計出來，依照遊戲的規則：
		-為了與Game board的窗口匹配，一格方塊的建議大小為20x20 pixel
		-設計出七種四格骨牌
		-旋轉時，以設為中心的方塊為基準
		-遊戲開始時，從Game board最上方中間的位置落下(由於窗口大小是10*20，落下起始在橫排10格方塊中間的兩格最上方)
		-當方塊下落到Game board最下方，或落到其他方塊上，無法再向下移動時，會固定在該處，換下一個新的隨機方塊落下
		-某一橫行的格子全部由方塊填滿時，會被消除並成為玩家的得分
		-當四格骨牌固定時，碰到Game board最上排的位置，遊戲會結束

	3.需要實現遊戲功能的鍵盤按鈕配置，以下為範例：
		-上：開始執行遊戲
		-下：方塊加速往下
		-左：方塊左移(單位一格)
		-右：方塊右移(單位一格)
		-Z：方塊逆時針旋轉
		-X：方塊順時針旋轉
		-P：遊戲暫停

	4. Bonus：
		a.遊戲可以中途暫停、重新開始
		b.遊戲結束畫面除了Game over以外，可以添加其他設計

	
