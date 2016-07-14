'''
    emotions:
    0=neutral,
    1=anger,
    2=contempt,
    3=disgust,
    4=fear,
    5=happy,
    6=sadness,
    7=surprise
    '''
import subprocess
import shlex
import os,fnmatch, sys
import numpy as np
import csv

def findFiles(pattern,path):
    result=[]
    print path
    for root, dirs, files in os.walk(path):
        for name in files:
            print name
            if fnmatch.fnmatch(name, pattern):
                result.append(os.path.join(root, name))

    return result

def buildDataSet(emotionFilesPaths):
    #dataSet=numpy.zeros((327,44))
    dataSet=[]
    linesNames=[]
    for i in range(len(emotionFilesPaths)):
        landmarksFilePath=emotionFilesPaths[i].replace('Emotion', 'Landmarks')
        landmarksFilePath=landmarksFilePath.replace('emotion','landmarks')

        name=landmarksFilePath[landmarksFilePath.rindex('/')+1:landmarksFilePath.rindex('_')]
        
        print emotionFilesPaths[i], landmarksFilePath, name
        emotion=np.genfromtxt(emotionFilesPaths[i])
        landmarks=np.genfromtxt(landmarksFilePath)
        
        linesNames.append(name)
        dataLine=[0] * 70
        dataLine[0]=name
        dataLine[44]=emotion[()]
        
        
        print landmarksFilePath, landmarks.ndim
        if landmarks.ndim==2:
            for j in range(len(landmarks)):
                AU_index=int(landmarks[j][0])
                if AU_index<44:
                    dataLine[AU_index]=int(landmarks[j][1])
                else:
                    print landmarks[j]
        else:
            AU_index=int(landmarks[0])
            if AU_index < 44:
                dataLine[AU_index]=int(landmarks[1])
            else:
                print landmarks
                    
        print dataLine
        dataSet.append(dataLine)
        #if i>5:
        #	break
    return dataSet

def writeDataToCSV(dataSet):
    writer=csv.writer(open("CKPlus_Landmarks_Emotion_Recognition_DataSet.csv", 'wb'),delimiter=',')
    writer.writerows(dataSet)


print 'create a single dataset from Cohn Kanade plus dataset...'
emotionFilesPaths=findFiles('*.txt', str(sys.argv[1]))
print len(emotionFilesPaths)
dataSet=buildDataSet(emotionFilesPaths)
#writeDataToCSV(dataSet)