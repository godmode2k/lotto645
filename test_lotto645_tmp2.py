# -*- coding: utf-8 -*-
"""
Created on Sun Apr 25 14:29:15 2021
# -----------------------------------------------------------------
# Purpose: Lotto 645 prediction test
# Author: Ho-Jung Kim (godmode2k@hotmail.com)
# Filename: test_lotto645.py
# Date: Since April 25, 2021
#
#
# Reference:
#
#
# License:
#
# *
# * Copyright (C) 2021 Ho-Jung Kim (godmode2k@hotmail.com)
# *
# * Licensed under the Apache License, Version 2.0 (the "License");
# * you may not use this file except in compliance with the License.
# * You may obtain a copy of the License at
# *
# *      http://www.apache.org/licenses/LICENSE-2.0
# *
# * Unless required by applicable law or agreed to in writing, software
# * distributed under the License is distributed on an "AS IS" BASIS,
# * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# * See the License for the specific language governing permissions and
# * limitations under the License.
# *
# -----------------------------------------------------------------
# Note:
# -----------------------------------------------------------------
# 1. Dependencies
#   $ pip install numpy
#   $ pip install scikit-learn
#
#   $ pip install micromlgen
#   or
#   $ pip install git+https://github.com/eloquentarduino/micromlgen.git
# -----------------------------------------------------------------
"""

import pandas as pd
import numpy as np
#import matplotlib as mpl
#import matplotlib.pyplot as plt

from sklearn.svm import SVC



"""
# ---------------------------------
# CSV
#
# download (Excel: xls): https://www.dhlottery.co.kr/gameResult.do?method=byWin
#
# CSV (.csv) file (modified)
# ----------------------------------------------------------------
# game    date          1     2     3     4     5     6     bonus
# ----------------------------------------------------------------
# 1054    2023.02.11    14    19    27    28    30    45    33
# ................................................................
# 1       2002.12.07    10    23    29    33    37    40    16
# ----------------------------------------------------------------
# ---------------------------------
df = pd.read_csv( "./lotto645_dataset_latest.csv" )

df.head()
#df.describe()
#pd.set_option('display.expand_frame_repr', False)
#pd.reset_option('display.max_columns')

pd.options.display.float_format = "{:,.2f}".format
#print( df.describe() )

df.head( 0 )
print( df )
print()


'''
df["당첨금액"].plot(figsize=(20, 6))
plt.legend()
plt.show()
'''

df_1 = df[ ["1"] ]
df_2 = df[ ["2"] ]
df_3 = df[ ["3"] ]
df_4 = df[ ["4"] ]
df_5 = df[ ["5"] ]
df_6 = df[ ["6"] ]
df_b = df[ ["bonus"] ]

#print( df["1"] )
#print( df_1["1"] )
#print( f'{df_1["1"][1]}' )

#import sys
#sys.exit()


'''
for i in range(len(df_1)):
    #if i == 10:
    #    break
    
    print( "[{}] {}, {}, {}, {}, {}, {}, {}".format(
            i,
            df_1["1"][i],
            df_2["2"][i],
            df_3["3"][i],
            df_4["4"][i],
            df_5["5"][i],
            df_6["6"][i],
            df_b["bonus"][i]) )
print()
'''

df_1_count = df_1["1"].value_counts()
df_2_count = df_2["2"].value_counts()
df_3_count = df_3["3"].value_counts()
df_4_count = df_4["4"].value_counts()
df_5_count = df_5["5"].value_counts()
df_6_count = df_6["6"].value_counts()
df_b_count = df_b["bonus"].value_counts()

print( "df_1_count\n{}".format(df_1_count) )
#print()

df_count_merge = pd.merge( df_1_count, df_2_count, left_index=True, right_index=True, how="outer")
df_count_merge = pd.merge( df_count_merge, df_3_count, left_index=True, right_index=True, how="outer")
df_count_merge = pd.merge( df_count_merge, df_4_count, left_index=True, right_index=True, how="outer")
df_count_merge = pd.merge( df_count_merge, df_5_count, left_index=True, right_index=True, how="outer")
df_count_merge = pd.merge( df_count_merge, df_6_count, left_index=True, right_index=True, how="outer")
df_count_merge = pd.merge( df_count_merge, df_b_count, left_index=True, right_index=True, how="outer")
#pd.options.display.float_format = "{:,.0f}".format
print( df_count_merge )
#print()

df_count_merge["sum"] = df_count_merge.fillna(0).apply(
        lambda x: x["1"] + x["2"] + x["3"] + x["4"] + x["5"] + x["6"] + x["bonus"], axis=1 )
print( df_count_merge )
print()

result = df_count_merge.sort_values( by="sum", ascending=False )
#result = result.fillna(0)
print( result )
print()

#print( result["1"] )
#print( result["1"][1] )
#print()

#print( result.columns.values )
#print()

#print( df_count_merge.columns.values )
#print( df.columns.values )
#print( df.columns.values[0] )
#print( len(df) )
#print( df.iloc[0] )


#for a in range(len(result.columns.values) - 2):
#    print( result.columns.values[a] )
#print( result.columns[0], result.columns[1], result.columns[2], result.columns[3], result.columns[4], result.columns[5] )
#print( result["1"][1], result["2"][1], result["3"][1], result["4"][1], result["5"][1], result["6"][1] )
#print( result["1"][2], result["2"][2], result["3"][2], result["4"][2], result["5"][2], result["6"][2] )


#import sys
#sys.exit()
"""


#"""
# ---------------------------------
# Excel
#
# download (Excel: xls): https://www.dhlottery.co.kr/gameResult.do?method=byWin
#
# Excel (.xls) file (NOT modified)
# ---------------------------------
# https://dhlottery.co.kr/gameResult.do?method=allWinExel&gubun=byWin&nowPage=&drwNoStart=1&drwNoEnd=1140
_xls_filename = "./lotto645_당첨번호1140회차까지.xls"
xls_filename = _xls_filename
xls_filename2 = _xls_filename # comparison
#df = pd.read_excel( xls_filename )
#
#df_excel_list = pd.read_html( xls_filename )
#pd.options.display.float_format = "{:,.2f}".format
#df = pd.DataFrame( df_excel_list[1] )
#
df_excel_list = pd.read_html( xls_filename, skiprows=2 )
pd.options.display.float_format = "{:,.2f}".format
df = pd.DataFrame( df_excel_list[0] )
#print( df[0] ) # 년도
#print( df[1] ) # 회차
#print( df[2] ) # 추첨일
#print( df[13] ) # 당첨번호 1
#print( df[14] ) # 당첨번호 2
#print( df[15] ) # 당첨번호 3
#print( df[16] ) # 당첨번호 4
#print( df[17] ) # 당첨번호 5
#print( df[18] ) # 당첨번호 6
#print( df[19] ) # 당첨번호 보너스

# result:
#        0     1           2   3               4   5   ...  14  15  16  17  18  19
#0     2023  1083  2023.09.02  15  1,713,084,525원  72  ...   7  14  15  22  38  17
#1     2023  1082  2023.08.26   7  3,720,489,643원  62  ...  26  27  32  34  42  31
#...
#1082  2002     1  2002.12.07   0              0원   1  ...  23  29  33  37  40  16


last_game_result = list(
    [
         df.iloc[0][1],  # 회차
         df.iloc[0][2],  # 추첨일
    [
        df.iloc[0][13], # 당첨번호 1
        df.iloc[0][14], # 당첨번호 2
        df.iloc[0][15], # 당첨번호 3
        df.iloc[0][16], # 당첨번호 4
        df.iloc[0][17], # 당첨번호 5
        df.iloc[0][18], # 당첨번호 6
        df.iloc[0][19]  # 당첨번호 보너스
    ]
    ]
)
print( "last game result = ", last_game_result )




'''
df_1 = { "1": list(df[13]) } # start at [2]: df[13][2]
df_2 = { "2": list(df[14]) }
df_3 = { "3": list(df[15]) }
df_4 = { "4": list(df[16]) }
df_5 = { "5": list(df[17]) }
df_6 = { "6": list(df[18]) }
df_b = { "bonus": list(df[19]) }

del df_1["1"][:2]
del df_2["2"][:2]
del df_3["3"][:2]
del df_4["4"][:2]
del df_5["5"][:2]
del df_6["6"][:2]
del df_b["bonus"][:2]
'''

df_1 = { "1": df[13] } # start at [2]: df[13][2]
df_2 = { "2": df[14] }
df_3 = { "3": df[15] }
df_4 = { "4": df[16] }
df_5 = { "5": df[17] }
df_6 = { "6": df[18] }
df_b = { "bonus": df[19] }

#print( df_1["1"][1] )
#print( df_1["1"] )

# result:
#0        3
#1       21
#...
#1081     9
#1082    10



'''
del df_1["1"][0]
del df_1["1"][1]
del df_2["2"][0]
del df_2["2"][1]
del df_3["3"][0]
del df_3["3"][1]
del df_4["4"][0]
del df_4["4"][1]
del df_5["5"][0]
del df_5["5"][1]
del df_6["6"][0]
del df_6["6"][1]
del df_b["bonus"][0]
del df_b["bonus"][1]
'''

'''
df_1["1"][0] = 0
df_1["1"][1] = 0
df_2["2"][0] = 0
df_2["2"][1] = 0
df_3["3"][0] = 0
df_3["3"][1] = 0
df_4["4"][0] = 0
df_4["4"][1] = 0
df_5["5"][0] = 0
df_5["5"][1] = 0
df_6["6"][0] = 0
df_6["6"][1] = 0
df_b["bonus"][0] = 0
df_b["bonus"][1] = 0
'''

new_data = {}
new_data["1"] = df_1["1"]
new_data["2"] = df_2["2"]
new_data["3"] = df_3["3"]
new_data["4"] = df_4["4"]
new_data["5"] = df_5["5"]
new_data["6"] = df_6["6"]
new_data["bonus"] = df_b["bonus"]
pd2 = pd.DataFrame( new_data )

#print( f'{df_1["1"]}' )
#print( f'{df_1["1"][1]}' )

#import sys
#sys.exit()


'''
for i in range(len(df_1)):
    #if i == 10:
    #    break
    
    print( "[{}] {}, {}, {}, {}, {}, {}, {}".format(
            i,
            df_1["1"][i],
            df_2["2"][i],
            df_3["3"][i],
            df_4["4"][i],
            df_5["5"][i],
            df_6["6"][i],
            df_b["bonus"][i]) )
print()
'''

df_1_count = df_1["1"].value_counts()
df_2_count = df_2["2"].value_counts()
df_3_count = df_3["3"].value_counts()
df_4_count = df_4["4"].value_counts()
df_5_count = df_5["5"].value_counts()
df_6_count = df_6["6"].value_counts()
df_b_count = df_b["bonus"].value_counts()


#print( "df_1_count\n{}".format(df_1_count) )
#print()

# result:
#df_1_count
#13
#1     151
#2     121
#3     110
#...
#29      1
#25      1
#35      1
#Name: count, dtype: int64


df_game_merge = pd.merge( df_1["1"], df_2["2"], left_index=True, right_index=True, how="outer", suffixes=('_1', '_2')) # 'count_1', 'count_2'
df_game_merge = pd.merge( df_game_merge, df_3["3"], left_index=True, right_index=True, how="outer", suffixes=('', '')) # 'count' (current column label) // not duplicate label
df_game_merge = pd.merge( df_game_merge, df_4["4"], left_index=True, right_index=True, how="outer", suffixes=('_3', '_4')) # 'count_3' (set prev column label), 'count_4' (current column label)
df_game_merge = pd.merge( df_game_merge, df_5["5"], left_index=True, right_index=True, how="outer", suffixes=('', '')) # 'count' // not duplicate label
df_game_merge = pd.merge( df_game_merge, df_6["6"], left_index=True, right_index=True, how="outer", suffixes=('_5', '_6')) # 'count_5', 'count_6'
df_game_merge = pd.merge( df_game_merge, df_b["bonus"], left_index=True, right_index=True, how="outer", suffixes=('', '')) # 'count' (bonus column) // not duplicate label
#print( df_game_merge )
#print()

# result:
#      13  14  15  16  17  18  19
#0      3   7  14  15  22  38  17
#1     21  26  27  32  34  42  31
#2      1   9  16  23  24  38  17
#...
#1080  11  16  19  21  27  31  30
#1081   9  13  21  25  32  42   2
#1082  10  23  29  33  37  40  16


# ----------

#print( list(df_game_merge.iloc[0]) )


df_game_merge_with_odd_even = df_game_merge.copy()
df_game_merge_with_odd_even["odd"] = df_game_merge.fillna(0).apply(
    # 1, 2, 3, 4, 5, 6, bonus
    lambda x: x[13]%2 + x[14]%2 + x[15]%2 + x[16]%2 + x[17]%2 + x[18]%2 + x[19]%2, axis=1)
df_game_merge_with_odd_even["even"] = df_game_merge.fillna(0).apply(
    # 1, 2, 3, 4, 5, 6, bonus
    lambda x: 
        (1 if (x[13]%2 == 0) else 0) +
        (1 if (x[14]%2 == 0) else 0) + 
        (1 if (x[15]%2 == 0) else 0) + 
        (1 if (x[16]%2 == 0) else 0) + 
        (1 if (x[17]%2 == 0) else 0) + 
        (1 if (x[18]%2 == 0) else 0) + 
        (1 if (x[19]%2 == 0) else 0), axis=1)
print( df_game_merge_with_odd_even )
print()

# result:
#      13  14  15  16  17  18  19  odd  even
#0      3   7  14  15  22  38  17    4     3
#1     21  26  27  32  34  42  31    3     4
#2      1   9  16  23  24  38  17    4     3
#...
#1080  11  16  19  21  27  31  30    5     2
#1081   9  13  21  25  32  42   2    4     3
#1082  10  23  29  33  37  40  16    4     3


game_merge_with_odd_even_mid = (
    (df_game_merge_with_odd_even["odd"].sum() / len(df_game_merge_with_odd_even.index)),
    (df_game_merge_with_odd_even["even"].sum() / len(df_game_merge_with_odd_even.index)) )
print( "total rows = ", len(df_game_merge_with_odd_even.index) )
print( "odd, even mid = ", game_merge_with_odd_even_mid )
print()

# result:
#total rows =  1083
#odd, even mid =  (3.569713758079409, 3.430286241920591)


# ----------


df_game_merge_with_per_game = df_game_merge.copy()
df_game_merge_with_per_game["sum_per_game"] = df_game_merge.fillna(0).apply(
    # 1, 2, 3, 4, 5, 6, bonus
    lambda x: (x[13] + x[14] + x[15] + x[16] + x[17] + x[18] + x[19]), axis=1)
print( df_game_merge_with_per_game )
print()

# result:
#      13  14  15  16  17  18  19  sum_per_game
#0      3   7  14  15  22  38  17           116
#1     21  26  27  32  34  42  31           213
#2      1   9  16  23  24  38  17           128
#...
#1080  11  16  19  21  27  31  30           155
#1081   9  13  21  25  32  42   2           144
#1082  10  23  29  33  37  40  16           188


df_game_merge_with_per_game_mid = (
    (df_game_merge_with_per_game["sum_per_game"].sum() / len(df_game_merge_with_per_game.index)) )
print( "total rows = ", len(df_game_merge_with_per_game.index) )
print( "mid (sum_per_game) = ", df_game_merge_with_per_game_mid )
print()

# result:
#total rows =  1083
#mid (sum_per_game) =  160.74792243767314


# diff abs(prev-next)
# mid (diff abs(prev-next))
df_game_merge_with_per_game["diff_abs"] = df_game_merge.fillna(0).apply(lambda x: 0, axis=1)
for i in range( len(df_game_merge_with_per_game.index) ):
    #print( df_game_merge_with_per_game["sum_per_game"][i] )
    
    if i+1 >= len(df_game_merge_with_per_game.index):
        # last game (current)
        diff = 0
    else:
        # abs( prev(current) - next )
        diff = abs(df_game_merge_with_per_game["sum_per_game"][i] - df_game_merge_with_per_game["sum_per_game"][i+1])
        
    df_game_merge_with_per_game["diff_abs"][i] = diff

print( df_game_merge_with_per_game )
print()

# result:
#      13  14  15  16  17  18  19  sum_per_game  diff_abs
#0      3   7  14  15  22  38  17           116        97
#1     21  26  27  32  34  42  31           213        85
#2      1   9  16  23  24  38  17           128        73
#...
#1080  11  16  19  21  27  31  30           155        11
#1081   9  13  21  25  32  42   2           144        44
#1082  10  23  29  33  37  40  16           188         0


df_game_merge_with_per_game_mid = (
    (df_game_merge_with_per_game["diff_abs"].sum() / len(df_game_merge_with_per_game.index)) )
print( "total rows = ", len(df_game_merge_with_per_game.index) )
print( "mid (diff_abs) = ", df_game_merge_with_per_game_mid )
print()

# result:
#total rows =  1083
#mid (diff_abs) =  36.960295475530934


# ----------


df_game_merge_with_digits = df_game_merge.copy()
df_game_merge_with_digits["d01"] = df_game_merge.fillna(0).apply(
    # 1, 2, 3, 4, 5, 6, bonus
    lambda x: 
        (1 if (x[13] < 10) else 0) +
        (1 if (x[14] < 10) else 0) + 
        (1 if (x[15] < 10) else 0) +
        (1 if (x[16] < 10) else 0) + 
        (1 if (x[17] < 10) else 0) +
        (1 if (x[18] < 10) else 0) + 
        (1 if (x[19] < 10) else 0), axis=1)
df_game_merge_with_digits["d10"] = df_game_merge.fillna(0).apply(
    # 1, 2, 3, 4, 5, 6, bonus
    lambda x: 
        (1 if (x[13] >= 10 and x[13] < 20) else 0) +
        (1 if (x[14] >= 10 and x[14] < 20) else 0) + 
        (1 if (x[15] >= 10 and x[15] < 20) else 0) +
        (1 if (x[16] >= 10 and x[16] < 20) else 0) + 
        (1 if (x[17] >= 10 and x[17] < 20) else 0) +
        (1 if (x[18] >= 10 and x[18] < 20) else 0) + 
        (1 if (x[19] >= 10 and x[19] < 20) else 0), axis=1)
df_game_merge_with_digits["d20"] = df_game_merge.fillna(0).apply(
    # 1, 2, 3, 4, 5, 6, bonus
    lambda x: 
        (1 if (x[13] >= 20 and x[13] < 30) else 0) +
        (1 if (x[14] >= 20 and x[14] < 30) else 0) + 
        (1 if (x[15] >= 20 and x[15] < 30) else 0) +
        (1 if (x[16] >= 20 and x[16] < 30) else 0) + 
        (1 if (x[17] >= 20 and x[17] < 30) else 0) +
        (1 if (x[18] >= 20 and x[18] < 30) else 0) + 
        (1 if (x[19] >= 20 and x[19] < 30) else 0), axis=1)
df_game_merge_with_digits["d30"] = df_game_merge.fillna(0).apply(
    # 1, 2, 3, 4, 5, 6, bonus
    lambda x: 
        (1 if (x[13] >= 30 and x[13] < 40) else 0) +
        (1 if (x[14] >= 30 and x[14] < 40) else 0) + 
        (1 if (x[15] >= 30 and x[15] < 40) else 0) +
        (1 if (x[16] >= 30 and x[16] < 40) else 0) + 
        (1 if (x[17] >= 30 and x[17] < 40) else 0) +
        (1 if (x[18] >= 30 and x[18] < 40) else 0) + 
        (1 if (x[19] >= 30 and x[19] < 40) else 0), axis=1)
df_game_merge_with_digits["d40"] = df_game_merge.fillna(0).apply(
    # 1, 2, 3, 4, 5, 6, bonus
    lambda x: 
        (1 if (x[13] >= 40 and x[13] <= 45) else 0) +
        (1 if (x[14] >= 40 and x[14] <= 45) else 0) + 
        (1 if (x[15] >= 40 and x[15] <= 45) else 0) +
        (1 if (x[16] >= 40 and x[16] <= 45) else 0) + 
        (1 if (x[17] >= 40 and x[17] <= 45) else 0) +
        (1 if (x[18] >= 40 and x[18] <= 45) else 0) + 
        (1 if (x[19] >= 40 and x[19] <= 45) else 0), axis=1)
print( df_game_merge_with_digits )
print()

# result:
#      13  14  15  16  17  18  19  d01  d10  d20  d30  d40
#0      3   7  14  15  22  38  17    2    3    1    1    0
#1     21  26  27  32  34  42  31    0    0    3    3    1
#2      1   9  16  23  24  38  17    2    2    2    1    0
#...
#1080  11  16  19  21  27  31  30    0    3    2    2    0
#1081   9  13  21  25  32  42   2    2    1    2    1    1
#1082  10  23  29  33  37  40  16    0    2    2    2    1


df_game_merge_with_digits_mid = (
    ("1", df_game_merge_with_digits["d01"].sum(), (df_game_merge_with_digits["d01"].sum() / len(df_game_merge_with_digits.index))),
    ("10", df_game_merge_with_digits["d10"].sum(), (df_game_merge_with_digits["d10"].sum() / len(df_game_merge_with_digits.index))),
    ("20", df_game_merge_with_digits["d20"].sum(), (df_game_merge_with_digits["d20"].sum() / len(df_game_merge_with_digits.index))),
    ("30", df_game_merge_with_digits["d30"].sum(), (df_game_merge_with_digits["d30"].sum() / len(df_game_merge_with_digits.index))),
    ("40", df_game_merge_with_digits["d40"].sum(), (df_game_merge_with_digits["d40"].sum() / len(df_game_merge_with_digits.index))) )
print( "total rows = ", len(df_game_merge_with_odd_even.index) )
print( "digits mid ((digits, sum,) 1, 10, 20, 30, 40) =\n", df_game_merge_with_digits_mid )
print()

# result:
#total rows =  1083
#digits mid ((digits, sum,) 1, 10, 20, 30, 40) =
#(( 1, 1502, 1.3868882733148662),
# (10, 1739, 1.605724838411819),
# (20, 1624, 1.4995383194829177),
# (30, 1711, 1.579870729455217),
# (40, 1005, 0.9279778393351801))


# export to C/C++ header
#float digits_mid_code[5][3] = {
#    { 1, 1502, 1.3868882733148662 },
#    { 10, 1739, 1.605724838411819 },
#    { 20, 1624, 1.4995383194829177 },
#    { 30, 1711, 1.579870729455217 },
#    { 40, 1005, 0.9279778393351801 },
#};

digits_mid_code_str = "float digits_mid_code[5][3] = {\n" \
    + str("    // [0]  1, 1502, 1.3868882733148662\n") \
    + str("    // [1] 10, 1739, 1.605724838411819\n") \
    + str("    // [2] 20, 1624, 1.4995383194829177\n") \
    + str("    // [3] 30, 1711, 1.579870729455217\n") \
    + str("    // [4] 40, 1005, 0.9279778393351801\n\n") \
    + str("    // [digits] [sum] [1] [10] [20] [30] [40]\n\n")
for i in range(0, len(df_game_merge_with_digits_mid)):
    digits_mid_code_str += "    { " \
        + str(df_game_merge_with_digits_mid[i][0]) + ", " \
        + str(df_game_merge_with_digits_mid[i][1]) + ", " \
        + str(df_game_merge_with_digits_mid[i][2]) + "f, " \
        + "},\n"
    #print( digits_mid_code_str )

digits_mid_code_str += str("};")
print( digits_mid_code_str )


# ----------


df_count_merge = pd.merge( df_1_count, df_2_count, left_index=True, right_index=True, how="outer", suffixes=('_1', '_2')) # 'count_1', 'count_2'
df_count_merge = pd.merge( df_count_merge, df_3_count, left_index=True, right_index=True, how="outer", suffixes=('', '')) # 'count' (current column label) // not duplicate label
df_count_merge = pd.merge( df_count_merge, df_4_count, left_index=True, right_index=True, how="outer", suffixes=('_3', '_4')) # 'count_3' (set prev column label), 'count_4' (current column label)
df_count_merge = pd.merge( df_count_merge, df_5_count, left_index=True, right_index=True, how="outer", suffixes=('', '')) # 'count' // not duplicate label
df_count_merge = pd.merge( df_count_merge, df_6_count, left_index=True, right_index=True, how="outer", suffixes=('_5', '_6')) # 'count_5', 'count_6'
df_count_merge = pd.merge( df_count_merge, df_b_count, left_index=True, right_index=True, how="outer", suffixes=('', '')) # 'count' (bonus column) // not duplicate label
#pd.options.display.float_format = "{:,.0f}".format
#print( df_count_merge )
#print()

# result:
#    count_1  count_2  count_3  count_4  count_5  count_6  count (<- bonus)
#1    151.00      NaN      NaN      NaN      NaN      NaN     30
#2    121.00    21.00      NaN      NaN      NaN      NaN     29
#3    110.00    34.00     3.00      NaN      NaN      NaN     26
#...
#43      NaN      NaN      NaN     2.00    30.00   118.00     35
#44      NaN      NaN      NaN      NaN    12.00   131.00     22
#45      NaN      NaN      NaN      NaN      NaN   157.00     17


df_count_merge["sum"] = df_count_merge.fillna(0).apply(
    # 1, 2, 3, 4, 5, 6, bonus
    
    # old
    #lambda x: x["1"] + x["2"] + x["3"] + x["4"] + x["5"] + x["6"] + x["bonus"], axis=1 )
    #lambda x: x[13] + x[14] + x[15] + x[16] + x[17] + x[18] + x[19], axis=1 )
    
    # new
    lambda x: x["count_1"] + x["count_2"] + x["count_3"] + x["count_4"] + x["count_5"] + x["count_6"] + x["count"], axis=1 )
print( df_count_merge )
print()

# result:
#    count_1  count_2  count_3  count_4  count_5  count_6  count (<- bonus)  sum
#1    151.00      NaN      NaN      NaN      NaN      NaN     30             181.00
#2    121.00    21.00      NaN      NaN      NaN      NaN     29             171.00
#3    110.00    34.00     3.00      NaN      NaN      NaN     26             173.00
#...
#43      NaN      NaN      NaN     2.00    30.00   118.00     35             185.00
#44      NaN      NaN      NaN      NaN    12.00   131.00     22             165.00
#45      NaN      NaN      NaN      NaN      NaN   157.00     17             174.00


result = df_count_merge.sort_values( by="sum", ascending=False )
result = result.fillna(0)
#columns_new = {"13": "1", "14": "2", "15": "3", "16": "4", "17": "5", "18": "6", "19": "bonus"}
columns_new = {result.columns[0]: "1", result.columns[1]: "2", result.columns[2]: "3",
               result.columns[3]: "4", result.columns[4]: "5", result.columns[5]: "6",
               result.columns[6]: "bonus"}
#print( list(map(int, result.index)) )
result.index = list(map(int, result.index))
result = result.rename( columns=columns_new )
print( "result:" )
print( result )
print()

# result:
#        1     2     3     4     5      6  bonus    sum
#43   0.00  0.00  0.00  2.00 30.00 118.00     35 185.00
#34   0.00  3.00 11.00 43.00 75.00  32.00     21 185.00
#27   1.00 16.00 36.00 54.00 40.00  10.00     28 185.00
#...
#29   1.00  5.00 32.00 41.00 46.00   9.00     14 148.00
#22   5.00 21.00 43.00 38.00 19.00   3.00     14 143.00
#9   39.00 54.00 18.00  4.00  1.00   0.00     24 140.00


# ----------


# export to C/C++ header
#float odd_even_code[45][9] = {
#    // [ 0][0] 43   0.00  0.00  0.00  2.00 30.00 118.00     35 185.00
#    // [ 1][0] 34   0.00  3.00 11.00 43.00 75.00  32.00     21 185.00
#    // ...
#    // [44][0] 9   39.00 54.00 18.00  4.00  1.00   0.00     24 140.00
#
#    // 1 ~ 45, appear counts
#    // [N] [1] [2] [3] [4] [5] [6] [bonus] [sum]
#    { 43, 0.00, 0.00, 0.00, 2.00, 30.00, 118.00, 35, 185.00 },
#    { 34, 0.00, 3.00, 11.00, 43.00, 75.00, 32.00, 21, 185.00 },
#    //...
#    { 9, 39.00, 54.00, 18.00, 4.00, 1.00, 0.00, 24 140.00 }
#};

#odd_even_code = None
odd_even_code_str = "float odd_even_code[45][9] = {\n" \
    + str("    // [ 0][0] 43   0.00  0.00  0.00  2.00 30.00 118.00     35 185.00\n") \
    + str("    // [ 1][0] 34   0.00  3.00 11.00 43.00 75.00  32.00     21 185.00\n") \
    + str("    // ...\n") \
    + str("    // [44][0] 9   39.00 54.00 18.00  4.00  1.00   0.00     24 140.00\n\n") \
    + str("    // 1 ~ 45, appear counts\n") \
    + str("    // [N] [1] [2] [3] [4] [5] [6] [bonus] [sum]\n\n")
for i in range(0, len(result.index)):
    #print( result.iloc[[i]], result.index[i] )
    #print( result.iloc[[i]]["1"], result.index[i] )
    #print( result.iloc[[i]]["2"], result.index[i] )
    #print( result.iloc[[i]]["3"], result.index[i] )
    #print( result.iloc[[i]]["4"], result.index[i] )
    #print( result.iloc[[i]]["5"], result.index[i] )
    #print( result.iloc[[i]]["6"], result.index[i] )
    #print( result.iloc[[i]]["bonus"], result.index[i] )
    #print( result.iloc[[i]]["sum"], result.index[i] )
    
    #_odd_even_code = np.hstack(
    #    (result.iloc[[i]]["1"],
    #    result.iloc[[i]]["2"],
    #    result.iloc[[i]]["3"],
    #    result.iloc[[i]]["4"],
    #    result.iloc[[i]]["5"],
    #    result.iloc[[i]]["6"],
    #    result.iloc[[i]]["bonus"],
    #    result.iloc[[i]]["sum"]))
    #odd_even_code = _odd_even_code if odd_even_code is None \
    #    else np.vstack((odd_even_code, _odd_even_code))
    #print( _odd_even_code )
    
    odd_even_code_str += "    { " \
        + str(result.index[i]) + ", " \
        + str(result.iloc[[i]].values[0][0]) + "f, " \
        + str(result.iloc[[i]].values[0][1]) + "f, " \
        + str(result.iloc[[i]].values[0][2]) + "f, " \
        + str(result.iloc[[i]].values[0][3]) + "f, " \
        + str(result.iloc[[i]].values[0][4]) + "f, " \
        + str(result.iloc[[i]].values[0][5]) + "f, " \
        + str(result.iloc[[i]].values[0][6]) + "f, " \
        + str(result.iloc[[i]].values[0][7]) + "f, " \
        + "},\n"
    #print( odd_even_code_str )

odd_even_code_str += str("};")
print( odd_even_code_str )



# #define LAST_GAME   "1 ~ 1125회\n(2024년 06월 22일 추첨까지)"
# const char* last_game = "no.1057"; // range: no.1 ~ present
# int result_won[] = { 8, 13, 19, 27, 40, 45, 12 };
last_game_info_str = "" \
    + str( '#define LAST_GAME   "1 ~ ' + str(last_game_result[0]) + '회\\n(' + str(last_game_result[1]) + ' 추첨까지)"\n') \
    + str( 'const char* last_game = "no.' + str(last_game_result[0]) + '"; // range: no.1 ~ present\n') \
    + str( "int result_won[] = { " ) \
    + str( last_game_result[2][0] ) + ", " \
    + str( last_game_result[2][1] ) + ", " \
    + str( last_game_result[2][2] ) + ", " \
    + str( last_game_result[2][3] ) + ", " \
    + str( last_game_result[2][4] ) + ", " \
    + str( last_game_result[2][5] ) + ", " \
    + str( last_game_result[2][6] ) \
    + str( " };\n" );

c_code_str = \
    "#ifndef __PREDICTS_METHOD__\n" + \
    "#define __PREDICTS_METHOD__\n\n" + \
    last_game_info_str + "\n\n" + \
    digits_mid_code_str + "\n\n" + \
    odd_even_code_str + "\n\n" + \
    "#endif // __PREDICTS_METHOD__"

print( "writing model_lotto645_predicts_method.h ..." )
with open('model_lotto645_predicts_method.h', 'w', encoding="UTF-8") as f:
#with open('model_lotto645_predicts_method.h', 'w', encoding="UTF-8-sig") as f:
    print(c_code_str, file=f)


# ----------


# ------------------------------
# for Odd, Even
# ------------------------------
# 1. split 10 rows from result
# 2. picks odd, even each 3 (odd, even:  3:3)

#        1     2     3     4     5      6  bonus    sum
#43   0.00  0.00  0.00  2.00 30.00 118.00     35 185.00
#34   0.00  3.00 11.00 43.00 75.00  32.00     21 185.00
#27   1.00 16.00 36.00 54.00 40.00  10.00     28 185.00
#17  18.00 45.00 50.00 31.00  9.00   0.00     30 183.00
#1  151.00  0.00  0.00  0.00  0.00   0.00     30 181.00
#12  38.00 62.00 41.00 13.00  2.00   0.00     25 181.00
#33   0.00  2.00 16.00 53.00 56.00  24.00     29 180.00
#18   7.00 50.00 59.00 33.00 11.00   1.00     18 179.00
#13  29.00 49.00 59.00 13.00  2.00   0.00     26 178.00
#20   5.00 31.00 61.00 34.00 16.00   4.00     25 176.00
# -----
#14  31.00 52.00 46.00 25.00  1.00   0.00     21 176.00
#4   97.00 44.00  4.00  0.00  0.00   0.00     30 175.00
#39   0.00  0.00  2.00 14.00 68.00  66.00     24 174.00
#26   3.00 13.00 38.00 54.00 31.00   6.00     29 174.00
#24   2.00 15.00 44.00 51.00 31.00   3.00     28 174.00
#45   0.00  0.00  0.00  0.00  0.00 157.00     17 174.00
#3  110.00 34.00  3.00  0.00  0.00   0.00     26 173.00
#38   0.00  0.00  3.00 23.00 62.00  57.00     28 173.00
#10  40.00 70.00 33.00  1.00  1.00   0.00     27 172.00
#6   82.00 44.00 12.00  3.00  0.00   0.00     31 172.00
# -----
#31   0.00  4.00 23.00 57.00 44.00  17.00     26 171.00
#2  121.00 21.00  0.00  0.00  0.00   0.00     29 171.00
#11  35.00 65.00 34.00 13.00  0.00   0.00     23 170.00
#40   0.00  0.00  1.00 14.00 52.00  83.00     20 170.00
#37   0.00  1.00  9.00 23.00 63.00  53.00     21 170.00
#35   1.00  0.00 11.00 38.00 53.00  39.00     28 170.00
#7   68.00 66.00 10.00  0.00  0.00   0.00     26 170.00
#15  13.00 53.00 53.00 23.00  3.00   0.00     23 168.00
#36   0.00  2.00  7.00 31.00 59.00  47.00     22 168.00
#16  22.00 38.00 48.00 31.00  3.00   0.00     26 168.00
# -----
#21   8.00 29.00 40.00 45.00 20.00   3.00     22 167.00
#44   0.00  0.00  0.00  0.00 12.00 131.00     22 165.00
#19  12.00 28.00 59.00 31.00 11.00   3.00     20 164.00
#30   0.00  7.00 32.00 47.00 34.00  12.00     30 162.00
#42   0.00  0.00  0.00  4.00 44.00  91.00     23 162.00
#5   88.00 46.00  5.00  1.00  0.00   0.00     21 161.00
#8   52.00 66.00 18.00  3.00  0.00   0.00     20 159.00
#32   0.00  3.00 13.00 47.00 45.00  21.00     29 158.00
#25   1.00 17.00 37.00 48.00 27.00   6.00     18 154.00
#28   0.00  4.00 36.00 38.00 42.00  11.00     21 152.00
# -----
#23   3.00 23.00 36.00 49.00 18.00   4.00     18 151.00
#41   0.00  0.00  0.00 10.00 52.00  72.00     15 149.00
#29   1.00  5.00 32.00 41.00 46.00   9.00     14 148.00
#22   5.00 21.00 43.00 38.00 19.00   3.00     14 143.00
#9   39.00 54.00 18.00  4.00  1.00   0.00     24 140.00

import random
odd_even_3_3 = list()
odd_even_3_3_not_selected = list()
result_odd_even_3_3 = list()
print( "result len = ", len(result.index) )
for i in range(0, len(result.index)):
    #print( result.iloc[[i]], result.index[i] )
    odd_even_3_3.append( result.index[i] )
    
    # len(result) = 45
    # 0  ~ 9
    # 10 ~ 19
    # 20 ~ 29
    # 30 ~ 39
    # 40 ~ 44
    if ( i > 0 and (i+1) % 10 == 0 ) or ( i+1 == len(result.index) ):
        #print( "i = ", i, "--------------------" )
        # last row (5 values) + un-selected values(?)
        if len(result_odd_even_3_3) == 4:
            odd_even_3_3.extend( odd_even_3_3_not_selected )
            
        odd_even_3_3 = list(set(odd_even_3_3))
        result_select = list()

        _odd_count = int(0)
        _even_count = int(0)
        _odd_count = len( list(filter(lambda x: x%2 != 0, odd_even_3_3)) )
        _even_count = len( list(filter(lambda x: x%2 == 0, odd_even_3_3)) )
        #_even_count = len( [i for i in odd_even_3_3 if (i % 2 == 0)] )
        #_odd_count = len(odd_even_3_3) - odd_even_3_3__even_count
        
        odd_count = int(0)
        even_count = int(0)
        
        print( "odd_even_3_3 = ", odd_even_3_3, ", odd = ", _odd_count, ", even = ", _even_count )
        
        loop_cnt = int(0)
        while len(result_select) < 6:
            #print( "odd_count = ", odd_count, "even_count = ", even_count )
            #print( "result_select len = ", len(result_select), "< 6" )
            sel = random.choices( odd_even_3_3, k=1 )
            
            #print( "odd_eve_3_3 = ", odd_even_3_3 )
            #print( "sel = ", sel, sel[0] )
            
            #print( "odd_count = ", odd_count, "even_count = ", even_count )            
            if sel not in result_select:
                #print( "not in result_select: selected" )
                #print( "result_select = ", result_select )
                #print()
                
                
                if (sel[0] % 2) != 0:
                    # odd
                    if odd_count < 3:
                        odd_count += 1
                        result_select.extend( sel )
                    elif ( i+1 == len(result.index) ):
                        print( "(odd) odd_count = ", odd_count, "even_count = ", even_count )
                        
                        if _even_count <= 1:
                            sel_new = int(0)
                            for i in odd_even_3_3:
                                if i % 2 != 0:
                                    sel_new = i - 1
                                    if sel_new <= 0:
                                        sel_new += 1
                                    if len(result_select) < 6 and [sel_new] not in result_select:
                                        result_select.extend( [sel_new] )
                                else:
                                    continue
                else:
                    # even
                    if even_count < 3:
                        even_count += 1
                        result_select.extend( sel )
                    elif ( i+1 == len(result.index) ):
                        print( "(even) odd_count = ", odd_count, "even_count = ", even_count )
                        
                        if _odd_count <= 1:
                            sel_new = int(0)
                            for i in odd_even_3_3:
                                if i % 2 == 0:
                                    sel_new = i + 1
                                    if sel_new > 45:
                                        sel_new -= 1
                                    if len(result_select) < 6 and [sel_new] not in result_select:
                                        result_select.extend( [sel_new] )
                                else:
                                    continue

            loop_cnt += 1
            
            if ( loop_cnt >= 10 ):
                while len(result_select) < 6:
                    #print( "select anyone either even or odd" )
                    sel = random.choices( odd_even_3_3, k=1 )
                    
                    #print( "sel = ", sel )
                    #print( "odd_count = ", odd_count, "even_count = ", even_count )            
                    
                    if sel not in result_select:
                        #print( "not in result_select: selected" )
                        #print( "result_select = ", result_select )
                        #print()
                        
                        #print( "--> ", _even_count, "==", even_count )
                        #print( "--> ", _odd_count, "==", odd_count )
                        
                        if _even_count == even_count:
                            #print( "odd_even_3_3__even_count == even_count" )
                            pass
                        else:
                            even_count += 1
                        
                        if _odd_count == odd_count:
                            #print( "odd_even_3_3__odd_count == odd_count" )
                            pass
                        else:
                            odd_count += 1
    
                        result_select.extend( sel )
                    
                    #print()
           
        result_odd_even_3_3.append( result_select )
        
        # last row (5 values) + un-selected values(?)
        if len(result_odd_even_3_3) < 5:
            #print( "odd_even_3_3 len =", len(odd_even_3_3) )
            for j in range(0, len(odd_even_3_3)):
                if odd_even_3_3[j] not in result_select:
                    odd_even_3_3_not_selected.extend( [odd_even_3_3[j]] )
                    
        odd_even_3_3.clear()

print("------------------------------")
print( "result #1:" )
#print( result_odd_even_3_3 )
for i in range(0, len(result_odd_even_3_3)):
    print( i, result_odd_even_3_3[i] )
print("------------------------------")
print()

# result:
#odd_even_3_3 =  [1, 34, 33, 43, 12, 13, 17, 18, 20, 27] , odd =  6 , even =  4
#odd_even_3_3 =  [3, 4, 38, 39, 6, 10, 45, 14, 24, 26] , odd =  3 , even =  7
#odd_even_3_3 =  [2, 35, 36, 37, 7, 40, 11, 15, 16, 31] , odd =  6 , even =  4
#odd_even_3_3 =  [32, 5, 8, 42, 44, 19, 21, 25, 28, 30] , odd =  4 , even =  6
#odd_even_3_3 =  [41, 9, 22, 23, 29] , odd =  4 , even =  1
#------------------------------
#result:
#0 [34, 27, 20, 1, 43, 12]
#1 [4, 10, 6, 3, 39, 45]
#2 [36, 16, 11, 40, 35, 15]
#3 [30, 8, 32, 19, 25, 21]
#4 [22, 9, 41, 29, 40, 8]
#------------------------------


# ----------


result_odd_even_3_3_flatten = list()
for i in range(0, len(result_odd_even_3_3)):
    #print( result_odd_even_3_3[i] )
    result_odd_even_3_3_flatten.extend( result_odd_even_3_3[i] )
    
print( result_odd_even_3_3_flatten )
print( "len = ", len(result_odd_even_3_3_flatten) )
print()


result_random_choice = list()
duplicate_sel = list()
func_search_val = lambda x, _sel: [i for i, v in enumerate(x) if v == _sel]
while len(result_random_choice) < 5:
    random_choice = list()
    
    while len(random_choice) < 6:
        """
        print( "result total: ", len(result_random_choice))
        print( result_random_choice)
        print( "---" )
        print( "current\n", random_choice )
        print( "---" )
        print( "duplicated numbers\n", duplicate_sel )
        print( "---" )
        print( "list = ", result_odd_even_3_3_flatten )
        print( "---" )
        """

        #print( len(result_odd_even_3_3_flatten), len(duplicate_sel) )

        sel_found = False
        sel = random.choices( result_odd_even_3_3_flatten, k=1 )
        
        if len(result_random_choice) == 0:
            if len(random_choice) > 0:
                if sel in random_choice:
                    sel_found = True
                    
                    idx = func_search_val( result_odd_even_3_3_flatten, sel )
                    if len(idx) > 0:
                        if [result_odd_even_3_3_flatten[idx[0]]] not in duplicate_sel:
                            duplicate_sel.extend( [result_odd_even_3_3_flatten[idx[0]]] ) # pick one (same value all)
                        # pop one
                        result_odd_even_3_3_flatten.pop( idx[0] )
        else:
            #print( "list = ", result_odd_even_3_3_flatten )
            
            for i in range(0, len(result_random_choice)):
                #print( "sel = ", sel, result_random_choice[i] )
                
                if sel in random_choice:
                    sel_found = True
                    #print( "#1: found...", sel )
                    
                    idx = func_search_val( result_odd_even_3_3_flatten, sel )
                    
                    #print( "list = ", result_odd_even_3_3_flatten )
                    #print( "idx = ", idx )
                    if len(idx) > 0:
                        #print( "result_odd_even_3_3_flatten[idx[0]] = ", result_odd_even_3_3_flatten[idx[0]] )
                        if [result_odd_even_3_3_flatten[idx[0]]] not in duplicate_sel:
                            duplicate_sel.extend( [result_odd_even_3_3_flatten[idx[0]]] ) # pick one (same value all)
                        # pop one
                        result_odd_even_3_3_flatten.pop( idx[0] )
                        
                    break
                
                if sel in result_random_choice[i]:
                    sel_found = True
                    #print( "#2 found...", sel )
                    
                    idx = func_search_val( result_odd_even_3_3_flatten, sel )
                    
                    #print( "list = ", result_odd_even_3_3_flatten )
                    #print( "idx = ", idx )
                    if len(idx) > 0:
                        #print( "result_odd_even_3_3_flatten[idx[0]] = ", result_odd_even_3_3_flatten[idx[0]] )
                        if [result_odd_even_3_3_flatten[idx[0]]] not in duplicate_sel:
                            duplicate_sel.extend( [result_odd_even_3_3_flatten[idx[0]]] ) # pick one (same value all)
                        # pop one
                        result_odd_even_3_3_flatten.pop( idx[0] )
                
                    break
                
        if sel_found == False:
            random_choice.extend( sel )
            #print( "   -> not found... add", sel, random_choice )
            idx = func_search_val( result_odd_even_3_3_flatten, sel )
            if len(idx) > 0:
                result_odd_even_3_3_flatten.pop( idx[0] )

    result_random_choice.append( random_choice )
    
print("------------------------------")
print( "result #2:" )
#print( result_random_choice )
for i in range(0, len(result_random_choice)):
    print( i, result_random_choice[i] )
print("------------------------------")
print()


# ----------


# ------------------------------
# test prediction
# source data (past data): 1 ~ x
# comparison (future data): x ~ 1112
# ------------------------------
#---
df_excel_list2 = pd.read_html( xls_filename2, skiprows=2 )
pd.options.display.float_format = "{:,.2f}".format
df2 = pd.DataFrame( df_excel_list2[0] )

df2_1 = { "1": df2[13] } # start at [2]: df[13][2]
df2_2 = { "2": df2[14] }
df2_3 = { "3": df2[15] }
df2_4 = { "4": df2[16] }
df2_5 = { "5": df2[17] }
df2_6 = { "6": df2[18] }
df2_b = { "bonus": df2[19] }

df2_1_count = df2_1["1"].value_counts()
df2_2_count = df2_2["2"].value_counts()
df2_3_count = df2_3["3"].value_counts()
df2_4_count = df2_4["4"].value_counts()
df2_5_count = df2_5["5"].value_counts()
df2_6_count = df2_6["6"].value_counts()
df2_b_count = df2_b["bonus"].value_counts()

df2_game_merge = pd.merge( df2_1["1"], df2_2["2"], left_index=True, right_index=True, how="outer", suffixes=('_1', '_2')) # 'count_1', 'count_2'
df2_game_merge = pd.merge( df2_game_merge, df2_3["3"], left_index=True, right_index=True, how="outer", suffixes=('', '')) # 'count' (current column label) // not duplicate label
df2_game_merge = pd.merge( df2_game_merge, df2_4["4"], left_index=True, right_index=True, how="outer", suffixes=('_3', '_4')) # 'count_3' (set prev column label), 'count_4' (current column label)
df2_game_merge = pd.merge( df2_game_merge, df2_5["5"], left_index=True, right_index=True, how="outer", suffixes=('', '')) # 'count' // not duplicate label
df2_game_merge = pd.merge( df2_game_merge, df2_6["6"], left_index=True, right_index=True, how="outer", suffixes=('_5', '_6')) # 'count_5', 'count_6'
df2_game_merge = pd.merge( df2_game_merge, df2_b["bonus"], left_index=True, right_index=True, how="outer", suffixes=('', '')) # 'count' (bonus column) // not duplicate label
#---

df_game_merge_test = df2_game_merge.copy()
#print( "len = ", len(df_game_merge_test.index) )
test_start_from = int(0)
result_matched_total_1 = int(0)
result_matched_total_2 = int(0)
result_matched_total_3 = int(0)
result_matched_total_4 = int(0)
result_matched_total_5 = int(0)
result_matched_total_6 = int(0)
result_matched_total = list()

# { no., 1~6+bonus }
results_winning_numbers_code_str = "int results_winning_numbers[][1+7] = {\n"
    
for i in range(test_start_from, len(df_game_merge_test.index)):
    #print( df_game_merge_test.iloc[[i]] )
    #print( df_game_merge_test.iloc[[i]].values[0] )
    #print( df_game_merge_test.iloc[[i]].values[0][0] )
    
    
    results_winning_numbers_code_str += "    { " \
        + str(df.iloc[i][1]) + ", " \
        + str(df_game_merge_test.iloc[[i]].values[0][0]) + ", " \
        + str(df_game_merge_test.iloc[[i]].values[0][1]) + ", " \
        + str(df_game_merge_test.iloc[[i]].values[0][2]) + ", " \
        + str(df_game_merge_test.iloc[[i]].values[0][3]) + ", " \
        + str(df_game_merge_test.iloc[[i]].values[0][4]) + ", " \
        + str(df_game_merge_test.iloc[[i]].values[0][5]) + ", " \
        + str(df_game_merge_test.iloc[[i]].values[0][6]) + ", " \
        + "},\n"
    #print( results_winning_numbers_code_str )

    

    for j in range(0, len(result_odd_even_3_3)):
        matched_count = int(0);
        #print( "[{}] comapre: {}".format(j, result_odd_even_3_3[j]) )
        #print( result_odd_even_3_3[j][0] )
        for k in range(0, 6):
            if result_odd_even_3_3[j][k] in df_game_merge_test.iloc[[i]].values[0]:
                matched_count += 1
                #print( "matched: ", result_odd_even_3_3[j][k] )

        #print( "  -> [{}] matched total: {}".format(j, matched_count) )
        
        if matched_count == 1:
            result_matched_total_1 += 1
        elif matched_count == 2:
            result_matched_total_2 += 1
        elif matched_count == 3:
            result_matched_total_3 += 1
        elif matched_count == 4:
            result_matched_total_4 += 1
        elif matched_count == 5:
            result_matched_total_5 += 1
        elif matched_count == 6:
            result_matched_total_6 += 1            
            
        if matched_count > 3:
            #print( "(matched ", matched_count, ")", "no.", df.iloc[i][1], "==>", df_game_merge_test.iloc[[i]].values[0] )
            result_matched_total.append( [ matched_count, df.iloc[i][1], df_game_merge_test.iloc[[i]].values[0], result_odd_even_3_3[j] ] )
        
    #print()

results_winning_numbers_code_str += str("};")

print( "matched total from 1 to last game result")
print( "matched total 1: ", result_matched_total_1 )
print( "matched total 2: ", result_matched_total_2 )
print( "matched total 3: ", result_matched_total_3 )
print( "matched total 4: ", result_matched_total_4 )
print( "matched total 5: ", result_matched_total_5 )
print( "matched total 6: ", result_matched_total_6 )
print()
result_matched_total.sort( key=lambda result_matched_total: result_matched_total[0] )
for i in range(0, len(result_matched_total)):
    print( "(matched ", result_matched_total[i][0], ")", "no.", result_matched_total[i][1], "==>", result_matched_total[i][2], "gen: ", result_matched_total[i][3] )
print()


#print( results_winning_numbers_code_str )
c_code_str = \
    "#ifndef __RESULTS_WINNING_NUMBERS__\n" + \
    "#define __RESULTS_WINNING_NUMBERS__\n\n" + \
    results_winning_numbers_code_str + "\n\n" + \
    "#endif // __RESULTS_WINNING_NUMBERS__"

print( "writing model_lotto645_results_winning_numbers.h ..." )
with open('model_lotto645_results_winning_numbers.h', 'w', encoding="UTF-8") as f:
#with open('model_lotto645_results_winning_numbers.h', 'w', encoding="UTF-8-sig") as f:
    print(c_code_str, file=f)





#--- break ---

#import sys
#sys.exit()

# ----------


#print( result.columns )
#print( result.index )


#print( result["1"] )
#print( result["1"][1] )
#print()

#print( result.columns.values )
#print()

#print( df_count_merge.columns.values )
#print( df.columns.values )
#print( df.columns.values[0] )
#print( len(df) )
#print( df.iloc[0] )


#for a in range(len(result.columns.values) - 2):
#    print( result.columns.values[a] )
#print( result.columns[0], result.columns[1], result.columns[2], result.columns[3], result.columns[4], result.columns[5] )
#print( result["1"][1], result["2"][1], result["3"][1], result["4"][1], result["5"][1], result["6"][1] )
#print( result["1"][2], result["2"][2], result["3"][2], result["4"][2], result["5"][2], result["6"][2] )


#import sys
#sys.exit()
#"""


# ----------


# Train
# ------------------------------------------------
def load_features(df_features):
    dataset = None
    classmap = {}
    class_idx = 0

    '''
    #for class_idx in df_features.columns.values:
    for class_idx in range(len(df_features)):
        #class_name = df_features.columns.values[class_idx]
        class_name = df_features.iloc[class_idx][0] # sequence
        classmap[class_idx] = class_name
        #samples = np.loadtxt(filename, dtype=float, delimiter=',')


        #_len = len( list(_data.keys()) )
        #samples = np.zeros((_len, 7)) # 1 ~ 6 + bonus
        samples = np.zeros(7) # 1 ~ 6 + bonus

        samples[0] = df_features.iloc[class_idx][4]
        samples[1] = df_features.iloc[class_idx][5]
        samples[2] = df_features.iloc[class_idx][6]
        samples[3] = df_features.iloc[class_idx][7]
        samples[4] = df_features.iloc[class_idx][8]
        samples[5] = df_features.iloc[class_idx][9]
        samples[6] = df_features.iloc[class_idx][10]

        #print( samples )

        #print (samples)
        #labels = np.ones((len(samples), 1)) * class_idx
        labels = np.ones(len(samples)) * class_idx
        samples = np.hstack((samples, labels))
        dataset = samples if dataset is None else np.vstack((dataset, samples))
    '''
        
    '''
    samples = np.zeros((len(df_features), 7)) # 1 ~ 6 + bonus
    for class_idx in range(len(df_features)):
        #class_name = df_features.columns.values[class_idx]
        class_name = df_features.iloc[class_idx][0] # sequence
        classmap[class_idx] = class_name
        #samples = np.loadtxt(filename, dtype=float, delimiter=',')


        samples[class_idx][0] = df_features.iloc[class_idx][4]
        samples[class_idx][1] = df_features.iloc[class_idx][5]
        samples[class_idx][2] = df_features.iloc[class_idx][6]
        samples[class_idx][3] = df_features.iloc[class_idx][7]
        samples[class_idx][4] = df_features.iloc[class_idx][8]
        samples[class_idx][5] = df_features.iloc[class_idx][9]
        samples[class_idx][6] = df_features.iloc[class_idx][10]
        
        #print( samples )

        #print (samples)
        labels = np.ones((len(samples), 1)) * class_idx
        #labels = np.ones(len(samples)) * class_idx
        samples = np.hstack((samples, labels))
        dataset = samples if dataset is None else np.vstack((dataset, samples))
    '''
    
    
    #for class_idx in range(len(df_features.columns.values) -1): # 1 ~ 6, bonus (without sum)
    for class_idx in range(45):
        '''
        # 1 ~ 6 + bonus: each 1 ~ 45
        class_name = df_features.columns.values[class_idx]
        classmap[class_idx] = class_name

        samples = np.zeros((7, 45)) # 1 ~ 6 + bonus: each 1 ~ 45

        for i in range(45):
            samples[class_idx][i] = df_features[class_name][i+1] # 1 ~ 45
            #print( "pos = [{}][{}] = {}".format(class_idx, i, samples[class_idx][i]))
        '''
        
        classmap[class_idx] = class_idx
        
        # 1 ~ 45: each 1 ~ 6 + bonus
        #samples = np.zeros((45, 7)) # 1 ~ 45: each 1 ~ 6 + bonus
        samples = np.zeros((45, 6)) # 1 ~ 45: each 1 ~ 6 (without bonus) 
        #for i in range(len(df_features.columns.values) -1): # 1 ~ 6, bonus (without sum)
        for i in range(len(df_features.columns.values) -2): # 1 ~ 6 (without bonus, sum)
            class_name = df_features.columns.values[i]
            #classmap[class_idx] = class_name
            
            samples[class_idx][i] = df_features[class_name][class_idx+1] # 1 ~ 6, bonus
            #print( "class_name = {}, pos = [{}][{}] = {}".format(class_name, class_idx, i, samples[class_idx][i]))


# result:
#class_name = 1, pos = [0][0] = 151.0
#class_name = 2, pos = [0][1] = nan
#class_name = 3, pos = [0][2] = nan
#class_name = 4, pos = [0][3] = nan
#class_name = 5, pos = [0][4] = nan
#class_name = 6, pos = [0][5] = nan
#class_name = 1, pos = [0][0] = 121.00
#...
#class_name = 6, pos = [1][5] = nan
#...
#class_name = 1, pos = [44][0] = nan
#class_name = 2, pos = [44][1] = nan
#class_name = 3, pos = [44][2] = nan
#class_name = 4, pos = [44][3] = nan
#class_name = 5, pos = [44][4] = nan
#class_name = 6, pos = [44][5] = 157.0


        samples[np.isnan(samples)] = 0
        
        labels = np.ones((len(samples), 1)) * class_idx
        #print( f'lables = {labels}' )
        samples = np.hstack((samples, labels))
        #print( f'samples = {samples}' )
        dataset = samples if dataset is None else np.vstack((dataset, samples))
        #print( f'dataset = {dataset}' )



    #print( labels )
    #print( samples )
    #print( dataset )
    #with np.printoptions(threshold=np.inf):
    #    print( dataset )


# result: labels
# [[0.] ... [0.]]
# ...
# [[44.] ... [44.]]

# result: dataset (samples)
# 0
#[[151.   0.   0.   0.   0.   0.   0.]
# ...
# [  0.   0.   0.   0.   0.   0.   0.]]
#
# 1
#[[  0.   0.   0.   0.   0.   0.   1.]
# [121.  21.   0.   0.   0.   0.   1.]
# ...
# [  0.   0.   0.   0.   0.   0.   1.]]
#
# ...
#
# 44
#[[  0.   0.   0.   0.   0.   0.  44.]
# [  0.   0.   0.   0.   0. 157.  44.]]


    return dataset, classmap


features, classmap = load_features( result )
#print (features)
#print (classmap)
X, y = features[:, :-1], features[:, -1]

# result: X
#[[151.   0.   0.   0.   0.   0.]
# [  0.   0.   0.   0.   0.   0.]
# [  0.   0.   0.   0.   0.   0.]
# ...
# [  0.   0.   0.   0.   0.   0.]
# [  0.   0.   0.   0.   0.   0.]
# [  0.   0.   0.   0.   0. 157.]]

# result: y
#[ 0.  0.  0. ... 44. 44. 44.]


# ----------


#import sys
#sys.exit()

'''
# Cross-Validation
# ------------------------------------------------
print( "GridSearchCV()..." )
from sklearn.model_selection import GridSearchCV
from sklearn.model_selection import train_test_split

param_grid = {'C':[0.001,0.01,0.1,1,10,100],'gamma':[0.001,0.01,0.1,1,10,100] }
grid_search = GridSearchCV(SVC(), param_grid, cv=5, return_train_score=True)
X_train, X_test, y_train, y_test = train_test_split(X, y, random_state=0, test_size=0.2)
grid_search.fit(X_train, y_train)
print("test set score : {}".format(grid_search.score(X_test, y_test)))
print("best parameters : {}".format(grid_search.best_params_))
print("best score : {}".format(grid_search.best_score_))
print()


# result:
# test set score : 0.009876543209876543
# best parameters : {'C': 0.001, 'gamma': 0.001}
# best score : 0.024074074074074074

import sys
sys.exit()
'''


# ----------


#"""
# ------------------------------------------------
classifier = SVC(kernel='rbf', gamma=0.001).fit(X, y)
#print (classifier)

# Export
# ------------------------------------------------
from micromlgen import port

# v1.1.2
c_code = port(classifier)

# save as 'model.h'
#print(c_code)

print( "writing model_lotto.h ..." )
with open('model_lotto645.h', 'w') as f:
    print(c_code, file=f)

print()
# ------------------------------------------------


# ----------


from numpy.random import seed
from numpy.random import randint
import random
#from numpy.random import choice
total_generate = 10*2
#total_generate = (100*5) * 3
total_games = 5
#result_won = [6,21,36,38,39,43,30] # no. 964
#result_won_game = "no.964"
#result_won = [9,18,20,22,38,44,10] # no. 964
#result_won = [6, 7, 22, 32, 35, 36, 19] # no. 964
#result_won_game = "no.1024"
result_won = last_game_result[2] # last game result
result_won_game = "no." + str( last_game_result[0] )
result_matched_all = []
result_matched_one_game = []
result_predict_all = []
generated_all_numbers = {}
print( "result won (" + result_won_game + "): ", result_won )
for x_gen in range(total_generate):
    for i in range(total_games): # 5 results
        result = np.zeros(6) # 1 ~ 6, bonus
        
        for j in range(6): # 1 ~ 6, bonus
            while True:
                #input_val = randint( 1, 45, 7 ) # 1 ~ 6, bonus
                input_val = randint( 1, 45, 6 ) # 1 ~ 6 (without bonus)
                #print( input_val )

                _result = classifier.predict( [input_val] ) # 0 ~ 44
                _result += 1 # start at 1
                    
                ## 50 : 50
                #if (j % 2) != 0:
                #    _result = classifier.predict( [input_val] ) # 0 ~ 44
                #    _result += 1 # start at 1
                #else:
                #    _result = choice( input_val )
                
                # Note
                #        1     2     3     4     5      6  bonus    sum
                #1  134.00   nan   nan   nan   nan    nan     29 163.00
                #45    nan   nan   nan   nan   nan 134.00     15 149.00
                
                if _result == 1 or _result == 45:
                    #input_val = randint( 2, 44, 6 ) # 1 ~ 6 (without bonus)
                    #_result = classifier.predict( [input_val] ) # 0 ~ 44
                    #_result += 1 # start at 1
                    #
                    input_val = randint( 1, 45, 1 ) # one number
                    _result = input_val
                    
                if _result in result:
                    continue

                #result[j] = _result
                result[j] = _result[0]
                break
            
        result_predict_all.append( result )
        
        # comparison
        result_matched = []
        for x in range(6):
            if result[x] in result_won:
                result_matched.append( result[x] )

        result_matched_all.extend( result_matched )
        #print( "result =", result, "==>", result_won_game + " matched(", len(result_matched), ")", result_matched )
        if len(result_matched_one_game) < len(result_matched):
            result_matched_one_game.clear()
            result_matched_one_game.extend( result_matched )
    
        '''
        result:
            
        result won (no.960): 2, 18, 24, 30, 32, 45 + 14
        result = [19. 27. 30.  1. 31. 35.] ==> no.960 matched( 1 ) [30.0]
        result = [ 9. 24. 25.  7. 37. 32.] ==> no.960 matched( 2 ) [24.0, 32.0]
        result = [ 2. 44. 19.  1. 18. 11.] ==> no.960 matched( 2 ) [2.0, 18.0]
        result = [ 3.  9. 38. 28. 23. 18.] ==> no.960 matched( 1 ) [18.0]
        result = [24. 30. 12. 27. 22. 31.] ==> no.960 matched( 2 ) [24.0, 30.0]
        result all (accumulative) (no.960) = [30.0, 24.0, 32.0, 2.0, 18.0] ==> count = 5
        result (no.960) = [24.0, 32.0] ==> count = 2
        '''

        
        '''
        # test
        # [ "sum": [array([x, x, x, x, x, x]), count_found], ... ]
        sum_result = 0
        for x in range(6):
            sum_result += result[x]
        if str(sum_result) in generated_all_numbers:
            # increase count found
            generated_all_numbers[str(sum_result)][1] = generated_all_numbers[str(sum_result)][1] + 1
        else:
            generated_all_numbers[str(sum_result)] = [result, 1]
        '''

        
        
    if (x_gen < (total_generate - 1)):
        result_matched_all.clear()
        result_matched_one_game.clear()
        result_predict_all.clear()
    #print( "total random generated = {}/{}".format(x_gen, total_generate - 1) )
    #print( "last game result = ", last_game_result )
    
    
result_matched_all = list( set(result_matched_all) ) # remove duplicate item
result_matched_one_game = list( set(result_matched_one_game) ) # remove duplicate item
print( "result all (accumulative) " + "(" + result_won_game + ") =", result_matched_all, "==> count =", len(result_matched_all) )
print( "result " + "(" + result_won_game + ") =", result_matched_one_game, "==> count =", len(result_matched_one_game) )
print()
print( "result predict all =" )
for i in range(len(result_predict_all)):
    print( i, result_predict_all[i] )

'''
result:

result predict all =
0 [19. 27. 30.  1. 31. 35.]
1 [ 9. 24. 25.  7. 37. 32.]
2 [ 2. 44. 19.  1. 18. 11.]
3 [ 3.  9. 38. 28. 23. 18.]
4 [24. 30. 12. 27. 22. 31.]
'''



'''
# test
print( "generated all numbers = " )
result_generated_all_numbers = []
for k in generated_all_numbers:
    #print( k, generated_all_numbers[k] )
    
    # [
    #  # key, numbers, count_found
    #  [142, array([22., 28.,  9., 16., 32., 35.]), 41],
    #  [133, array([22., 30., 23., 21., 28.,  9.]), 40],
    #  ...
    # ]
    _generated_all_numbers = generated_all_numbers[k]
    _generated_all_numbers.insert( 0, int(float(k)) ) # "key" to intger
    result_generated_all_numbers.append( _generated_all_numbers )
#print( result_generated_all_numbers )
#
# sort
# [
#  [142, array([22., 28.,  9., 16., 32., 35.]), 41],
#  [133, array([22., 30., 23., 21., 28.,  9.]), 40],
#  ...
# ]
result_generated_all_numbers.sort(key = lambda x: x[2], reverse=True)
for i in range(len(result_generated_all_numbers)):
    print( result_generated_all_numbers[i] )
'''



#"""

pass



# ----------



# SEE: https://eloquentarduino.github.io/2019/11/how-to-train-a-classifier-in-scikit-learn/
'''
from sklearn.ensemble import RandomForestClassifier

def get_classifier(features):
    X, y = features[:, :-1], features[:, -1]

    return RandomForestClassifier(20, max_depth=10).fit(X, y)
-----

from micromlgen import port

if __name__ == '__main__':
    features, classmap = load_features('your-data-folder')
    classifier = get_model(features)
    c_code = port(classifier, classmap=classmap)
    print(c_code)
-----

// put the code you got in Step 3 into this file
#include "model.h"

// this class will be different if you used another type of classifier, just check the model.h file
Eloquent::ML::Port::RandomForest classifier;

void classify() {
    float x_sample[] = { /* fill this vector with sample values */ };

    Serial.print("Predicted class: ");
    Serial.println(classifier.predictLabel(x_sample));
}

'''

