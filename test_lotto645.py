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
#   $ pip install sklearn
#   v1.1.2
#   $ pip install micromlgen
#   v1.1.3
#   $ pip uninstall micromlgen
#   $ pip install https://github.com/eloquentarduino/micromlgen.git
# -----------------------------------------------------------------
"""

import pandas as pd
import numpy as np
#import matplotlib as mpl
#import matplotlib.pyplot as plt

from sklearn.svm import SVC



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

#print( f'{df_1["1"][1]}' )


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
#print( df_count_merge )
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
        
        
        # 1 ~ 45: each 1 ~ 6 + bonus
        #samples = np.zeros((45, 7)) # 1 ~ 45: each 1 ~ 6 + bonus
        samples = np.zeros((45, 6)) # 1 ~ 45: each 1 ~ 6 (without bonus) 
        #for i in range(len(df_features.columns.values) -1): # 1 ~ 6, bonus (without sum)
        for i in range(len(df_features.columns.values) -2): # 1 ~ 6 (without bonus, sum)
            class_name = df_features.columns.values[i]
            classmap[class_idx] = class_name
            
            samples[class_idx][i] = df_features[class_name][class_idx+1] # 1 ~ 6, bonus
            print( "pos = [{}][{}] = {}".format(class_idx, i, samples[class_idx][i]))


        samples[np.isnan(samples)] = 0

        labels = np.ones((len(samples), 1)) * class_idx
        #print( f'lables = {labels}' )
        samples = np.hstack((samples, labels))
        #print( f'samples = {samples}' )
        dataset = samples if dataset is None else np.vstack((dataset, samples))
        #print( f'dataset = {dataset}' )
    
    return dataset, classmap


features, classmap = load_features( result )
#print (features)
#print (classmap)
X, y = features[:, :-1], features[:, -1]

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
# ------------------------------------------------




from numpy.random import seed
from numpy.random import randint
total_generate = 100
total_games = 5
result_won = [6,21,36,38,39,43,30] # no. 964
result_won_game = "no.964"
result_matched_all = []
result_matched_one_game = []
result_predict_all = []
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
                
                result[j] = _result
                break
            
        result_predict_all.append( result )
        
        # comparison
        result_matched = []
        for x in range(6):
            if result[x] in result_won:
                result_matched.append( result[x] )

        result_matched_all.extend( result_matched )
        print( "result =", result, "==>", result_won_game + " matched(", len(result_matched), ")", result_matched )
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
        
    if (x_gen < (total_generate - 1)):
        result_matched_all.clear()
        result_matched_one_game.clear()
        result_predict_all.clear()
    print( "total random generated = {}/{}".format(x_gen, total_generate - 1) )
    
    
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



#"""

pass





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

