import numpy as np
import pandas as pd 
from PIL import Image
from tqdm import tqdm
import os

# string to int
def atoi(s):
    n = 0
    for i in s:
        n = n*10 + ord(i) - ord("0")
    return n

# making folders
outer_names = ['test','train']
inner_names = ['angry', 'disgusted', 'fearful', 'happy', 'sad', 'surprised', 'neutral']
os.makedirs('data', exist_ok=True)
for outer_name in outer_names:
    os.makedirs(os.path.join('src', 'data',outer_name), exist_ok=True)
    for inner_name in inner_names:
        os.makedirs(os.path.join('src', 'data',outer_name,inner_name), exist_ok=True)

# to keep count of each category
angry = 0
disgusted = 0
fearful = 0
happy = 0
sad = 0
surprised = 0
neutral = 0
angry_test = 0
disgusted_test = 0
fearful_test = 0
happy_test = 0
sad_test = 0
surprised_test = 0
neutral_test = 0

df = pd.read_csv('./fer2013.csv')
mat = np.zeros((48,48),dtype=np.uint8)
print("Saving images...")

# read the csv file line by line
for i in tqdm(range(len(df))):
    txt = df['pixels'][i]
    words = txt.split()
    
    # the image size is 48x48
    for j in range(2304):
        xind = j // 48
        yind = j % 48
        mat[xind][yind] = atoi(words[j])

    img = Image.fromarray(mat)

    # train
    if i < 28709:
        if df['emotion'][i] == 0:
            img.save('src/data/train/angry/im'+str(angry)+'.png')
            angry += 1
        elif df['emotion'][i] == 1:
            img.save('src/data/train/disgusted/im'+str(disgusted)+'.png')
            disgusted += 1
        elif df['emotion'][i] == 2:
            img.save('src/data/train/fearful/im'+str(fearful)+'.png')
            fearful += 1
        elif df['emotion'][i] == 3:
            img.save('src/data/train/happy/im'+str(happy)+'.png')
            happy += 1
        elif df['emotion'][i] == 4:
            img.save('src/data/train/sad/im'+str(sad)+'.png')
            sad += 1
        elif df['emotion'][i] == 5:
            img.save('src/data/train/surprised/im'+str(surprised)+'.png')
            surprised += 1
        elif df['emotion'][i] == 6:
            img.save('src/data/train/neutral/im'+str(neutral)+'.png')
            neutral += 1

    # test
    else:
        if df['emotion'][i] == 0:
            img.save('src/data/test/angry/im'+str(angry_test)+'.png')
            angry_test += 1
        elif df['emotion'][i] == 1:
            img.save('src/data/test/disgusted/im'+str(disgusted_test)+'.png')
            disgusted_test += 1
        elif df['emotion'][i] == 2:
            img.save('src/data/test/fearful/im'+str(fearful_test)+'.png')
            fearful_test += 1
        elif df['emotion'][i] == 3:
            img.save('src/data/test/happy/im'+str(happy_test)+'.png')
            happy_test += 1
        elif df['emotion'][i] == 4:
            img.save('src/data/test/sad/im'+str(sad_test)+'.png')
            sad_test += 1
        elif df['emotion'][i] == 5:
            img.save('src/data/test/surprised/im'+str(surprised_test)+'.png')
            surprised_test += 1
        elif df['emotion'][i] == 6:
            img.save('src/data/test/neutral/im'+str(neutral_test)+'.png')
            neutral_test += 1

print("Done!")




##test
#Angry
angry_set= df[df["emotion"]==0]
angry_training = angry_set[angry_set["Usage"]=="Training"]
totalAngry = angry_training.count()

print(angry_training)
print(totalAngry)
print(totalAngry ==3995)

#Disgusted
disgusted_set= df[df["emotion"]==1]
disgusted_training = disgusted_set[disgusted_set["Usage"]=="Training"]
totalDisgusted = disgusted_training.count()

print(disgusted_training)
print(totalDisgusted)


#Fearful
fearful_set= df[df["emotion"]==2]
fearful_training = fearful_set[fearful_set["Usage"]=="Training"]
totalFearful = fearful_training.count()

print(fearful_training)
print(totalFearful)

#Happy
happy_set= df[df["emotion"]==3]
happy_training = happy_set[happy_set["Usage"]=="Training"]
totalHappy = happy_training.count()

print(happy_training)
print(totalHappy)

#Neutral

#Sad


#Surprised
