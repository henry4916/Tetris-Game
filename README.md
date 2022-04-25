# Tetris Game
## 計算攝影學：應用圖學與影像技術_HW2
## Demo：
[![IMAGE ALT TEXT](https://user-images.githubusercontent.com/72666141/165116969-931ec08b-a66b-49ff-85ec-86c45944a7f9.PNG)](https://www.youtube.com/watch?v=GRcNxCQtLs0)
## 指定作業功能：
	1.建立一個Tetris遊戲的視窗，包含四個要素：
		a.Game board：是你遊戲的主要窗口，大小為10*20，至少可容納200個方塊。(為了和方塊匹配，大小為200x400 pixel)
		b.Preview window：預覽窗口顯示下一個，將生成的方塊。
		c.Score display：顯示當前累積分數，消除一排方塊獲得10分，若同時消除越多排分數越高，mark = 10 * Combo * Combo，Combo = number of rows disappeared for a single block
		d.Level display：指當前難度，控制方塊的下落速度，分數每超過30分，上升難度，加快下落速度，實驗過投影片的公式但是速度太慢，所以調整為level有10個，每一個level有不同的速度

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
		-enter:遊戲重新開始

	4. Bonus：
		a.遊戲可以中途暫停、重新開始
		b.遊戲結束畫面除了Game over並顯示分數
![image](https://user-images.githubusercontent.com/72666141/139395990-bc618e8d-2054-4bb8-8220-0e786a1ebdda.png)

#### 參考資料：
https://blog.csdn.net/wangxh88/article/details/84219318
https://github.com/linzhi/tetris
https://blog.csdn.net/weixin_30569153/article/details/97128717?ops_request_misc=&request_id=&biz_id=102&utm_term=opengl%20tetris&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-1-97128717.nonecase&spm=1018.2226.3001.4187
https://github.com/TakashiL/OpenGL-Tetris
https://github.com/xhacker/tetris-opengl
https://github.com/AvronGols/tetris-opengl
https://github.com/xhacker/tetris-opengl
https://www.youtube.com/watch?v=-8teaOoZdxA
