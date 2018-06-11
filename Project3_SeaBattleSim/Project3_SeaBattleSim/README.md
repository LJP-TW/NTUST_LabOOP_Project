# 指令

```
SET [Vessel_Name] [Type] [2DCoordinate]
    [Vessel_Name] : 船艦名稱
        中間不能有空格, 而且同隊船艦不能重複存在
        
    [Type] : 艦種
        艦種必須是以下種類 :
    
    [2DCoordinate] : 座標
        座標表示方式需以以下格式 :
            ([double], [double])
                [double] : 雙精度浮點數
```

```
FIRE
```

```
DEFENSE
```

```
TAG
```

```
MOVE [Vessel_Name] [Speed] [Angle]
    [Vessel_Name] : 船艦名稱
        中間不能有空格, 而且船艦必須存在
    
    [Speed] : 速度
        船艦的速度會被直接設定成該速度, 不能超過該艦種的最高速限
        
    [Angle] : 角度
        船艦的角度會被直接設定成該角度, 0度為正右方, 逆時鐘方向旋轉
```