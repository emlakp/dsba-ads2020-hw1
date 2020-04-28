import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

x = np.array([])
f1= np.array([])
f2 = np.array([])
f3 = np.array([])


data = pd.read_csv('//Users//emilakopyan//Downloads//data.csv', delimiter=',')
x = data['Digits']
f1 = data['Karatsuba']
f2 = data['GradeSchool']
f3 = data['DivConquer']


plt.plot(x, f1,'r', x, f2, 'y', x, f3, 'g')
plt.legend(['Karatsuba', 'Grade school','Divide and conquer'])

plt.xlabel('Number of digits')
plt.ylabel('Millisecond ')

plt.savefig('line_plot1.png')

plt.show()

