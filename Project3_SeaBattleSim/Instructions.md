# NTUST OOP-LAB Project 3 
## 即時戰略遊戲 說明書 Sea Battle Sim Instructions

### [GitHub Link](https://github.com/LJP-TW/NTUST_LabOOP_Project/tree/master/Project3_SeaBattleSim)

### 介面說明
* 隊伍顏色：<font color=green>綠色為 ATeam</font>，<font color=blue>藍色為 BTeam</font>。
* 圖形分類： "▲" 為船艦， "★" 為武器。

![圖片說明](https://user-images.githubusercontent.com/4931242/41669231-eda78868-74e3-11e8-9856-ae29aea2d1b3.png)

### 艦種清單 
<font size=2>*(標註**粗體**為新增艦種)</font>

| 艦種  名稱 | HP | 最高航速 <font size=1>(單位/min) |攻擊  最大距離|攻擊CD   <font size=1>(sec)|防守  最大距離|防守CD   <font size=1>(sec)|武器  傷害|砲彈飛速   <font size=1>(單位/min)|
| :--------: | --------: | --------: |--------: |--------: |--------: |--------: |--------: |--------: |
| CV     | 5| 1 |25 |60 |5    |15 |3|4|
| BB     | 4| 1 |20 |30 |10   |30 |3|2|
| CG     | 2| 2 |15 |30 |15   |30 |2|3|
| DD     | 3| 3 |10 |15 |20   |60 |1|3|
| <font color=red>**FL**|<font color=red>**1**|<font color=red>**10**|<font color=red>**X**|<font color=red>**X**|<font color=red>**5**|<font color=red>**15** |<font color=red>**X**|<font color=red>**X**|
| <font color=red>**LJP**|<font color=red>**10**|<font color=red>**5**|<font color=red>**30**|<font color=red>**15**|<font color=red>**20**|<font color=red>**15** |<font color=red>**5**|<font color=red>**5**|

### 武器清單
<font size=2>*(標註<font color=red>粗體</font>為新增武器)</font>

|種類|傷害|飛速<font size=1><br>(單位/min)</font>|攻擊CD<br><font size=1>(sec)|攻擊<br>最大範圍|目標<br>追蹤|適用<br>艦種|
| :--------: | --------: | --------: |--------: | --------: | :--------: |:---:|
|Normal |依艦種設定|依艦種設定|依艦種設定|1.5|X|全部|
|<font color=red>**Missile** |<font color=red>**3**|<font color=red>**12**|<font color=red>**60**|<font color=red>**0.2**|<font color=red>**Ο**|<font color=red>**僅LJP**|

### 指令及相對應Log輸出
<font size=2>*(標註<font color=red>粗體</font>為新增指令或修改內容)</font>

* #### SET [Vessel_Name] [Type] [2DCoordinate]

	><font size=2> Log 輸出格式：
	> [mm:ss] [team] SET [Vessel_Name] with [Type] at [2DCoordinate] -> Success
	> [mm:ss] [team] SET [Vessel_Name] with [Type] at [2DCoordinate] -> Fail</font>
	
* #### FIRE [Vessel_Name] [2DCoordinate]
	* 發射砲彈攻擊某座標：攻擊船艦名字[Vessel_Name]、攻擊座標(中心點)[2DCoordinate]。
	* 攻擊船艦必須在場上且存在於該隊。
	* [2DCoordinate]的範圍在攻擊最大距離內。
	* 自動對該砲彈命名，砲彈名字: Shell_(team+id)，其id為發射順序。
	* (ex. Shell_A1為A艦隊第1個發射的<font color=red>**武器**</font>)
	* 攻擊後就進入CD時間
	* Ex: FIRE CV-1 (0.0, 10.0) //Shell_A1 出現，CV-1進入攻擊CD(冷卻)時間
	
	><font size=2> Log 輸出格式：
	> [mm:ss] [team] [Vessel_Name] FIRE to [2DCoordinate] -> [Shell_Name]
	> [mm:ss] [team] [Vessel_Name] FIRE to [2DCoordinate] -> Fail
	</font>
	

* **#### <font color=red> MISSILE [Fire_Vessel_Name] [Target_Vessel_Name]</font>**
	* **發射**導彈**攻擊敵方船艦：攻擊船艦名字[Fire_Vessel_Name]、目標船艦名字[Fire_Vessel_Name]。**
	* **攻擊船艦艦種必須為 **LJP** **且在場上並存在於該隊。**
	* **目標船艦必須在場上且存在於敵隊，不限制攻擊艦種。**
	* **自動對該砲彈命名，砲彈名字: Missile_(team+id)，其id為發射順序。**
	* **(ex. Missile_A1為A艦隊第1個發射的武器)**
	* **攻擊後就進入MissileCD時間**
	* **獨立計算CD時間，不受其他武器CD時間影響。**
	* **Ex: MISSILE LJP-1 CV-1  //Missile_A1 出現，LJP-1進入MissileCD(冷卻)時間**
	
	><font size=2> Log 輸出格式：
	> [mm:ss] [team] [Vessel_Name] Missile_FIRE to [2DCoordinate] -> [Shell_Name]
	> [mm:ss] [team] [Vessel_Name] Missile_FIRE to [2DCoordinate] -> Fail
	</font>

* #### DEFENSE [Vessel_Name] [Shell_Name]
	><font size=2> Log 輸出格式：
	> [mm:ss] [Vessel_Name] DEFENSE [Shell_Name] -> Hit
	> [mm:ss] [Vessel_Name] DEFENSE [Shell_Name] -> Fail
	</font>

* #### TAG [Vessel_Name] [New_Name]
	><font size=2> Log 輸出格式：
	> [mm:ss] [team] RENAME [Vessel_Name] to [New_Name] -> Success
	> [mm:ss] [team] RENAME [Vessel_Name] to [New_Name] -> Fail
	</font>

* #### MOVE [Vessel_Name] [Speed] [Angle]
	><font size=2> Log 輸出格式：
	> [mm:ss] [team] [Vessel_NameA] MOVE to [Angle] as [Speed] -> Success
	> [mm:ss] [team] [Vessel_NameA] MOVE to [Angle] as [Speed] -> Fail
	</font>

### 區域警示 <font size=3>（新增）</font>
* #### 文字顯示 (Log輸出)
	* 當武器接近目標（武器與目標直線距離為**3單位**）時輸出Log。
	* 格式：**[mm:ss] WARRNING [Weapon_Name] is Approaching Target !!!**
	* 範例：[00:37] WARRNING Shell_A1 is Approaching Target !!!
* #### 圖形化顯示
	* 會依據武器接近目標距離遠近，顯示以攻擊範圍為半徑的不同深淺紅色圓形。
	* 圓形顏色 **從淺至深** → 武器到目標距離 **從遠至近**
	
	![red_explain](https://user-images.githubusercontent.com/4931242/41671077-a2170ee6-74e8-11e8-9abc-98b492a3f0b5.png)
	* 實際操作情形<br>
	![example](https://user-images.githubusercontent.com/4931242/41670926-3b38dccc-74e8-11e8-980f-d4ce1a45e299.png)


