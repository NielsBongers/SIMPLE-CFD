import matplotlib.pyplot as plt
import matplotlib.patches as patches
import numpy as np
import pandas as pd
import sys
import math

path = sys.path[0] + "\\u.txt"
uMatrix = pd.read_csv(path, delimiter="\t", error_bad_lines=False, header=None).to_numpy()

path = sys.path[0] + "\\v.txt"
vMatrix = pd.read_csv(path, delimiter="\t", error_bad_lines=False, header=None).to_numpy()

path = sys.path[0] + "\\p.txt"
pMatrix = pd.read_csv(path, delimiter="\t", error_bad_lines=False, header=None).to_numpy()

path = sys.path[0] + "\\speed.txt"
speedMatrix = pd.read_csv(path, delimiter="\t", error_bad_lines=False, header=None).to_numpy()

f1 = plt.figure(1)

plt.imshow(uMatrix, cmap='jet', interpolation='none')#, aspect='auto')
ax = plt.gca()

cbar = plt.colorbar()
cbar.set_label('Flow speed (m/s)')
#plt.clim(-0.5,2)
plt.gca().invert_yaxis()
ax = plt.gca().set_xlim(left=1)
plt.ylabel("y") 
plt.xlabel("x")
plt.title("Reference case") 

f2 = plt.figure(2)

plt.imshow(vMatrix, cmap='jet', interpolation='none')#, aspect='auto')
ax = plt.gca()

cbar = plt.colorbar()
cbar.set_label('Flow speed (m/s)')
#plt.clim(-0.5,2)
plt.gca().invert_yaxis()
ax = plt.gca().set_xlim(left=1)
plt.ylabel("y") 
plt.xlabel("x")
plt.title("Reference case") 

f3 = plt.figure(3)

plt.imshow(pMatrix, cmap='jet', interpolation='none')#, aspect='auto')
ax = plt.gca()
cbar = plt.colorbar()
cbar.set_label('Pressure (bar)')
plt.gca().invert_yaxis()
ax = plt.gca().set_xlim(left=1)
plt.ylabel("y") 
plt.xlabel("x")

plt.title("Reference case") 
plt.savefig("D:\\Google Drive\\Cpp\\SIMPLE\\pressure.png",bbox_inches='tight')
#plt.savefig("C:\\Users\\Niels\\Google Drive\\Cpp\\SIMPLE\\pressure.png",bbox_inches='tight')

f4 = plt.figure(4)

#x = np.arange(0, uMatrix.shape[0], 10)
#y = np.arange(0, vMatrix.shape[0], 10)

#print(np.add.outer(x,y))

#plt.quiver(np.add.outer(x,y), np.add.outer(x,y), uMatrix[x,y], vMatrix[x,y], scale = 10)

#plt.quiver(uMatrix, vMatrix, scale = 100)
#plt.contour(speedMatrix, cmap='jet', levels=50, linewidths=1.5)
plt.imshow(speedMatrix, cmap='jet', interpolation='bicubic')#, aspect='auto')
ax = plt.gca()
rect = patches.Rectangle((31, -2), 10, 20, linewidth=0, edgecolor='b', facecolor='w')
#circ = patches.Circle((101, 198), 5, facecolor='w')
#ax.add_patch(rect)
#ax.add_patch(circ)



cbar = plt.colorbar()
cbar.set_label('Flow speed (m/s)')
#plt.clim(-0.5,2)
plt.gca().invert_yaxis()
ax = plt.gca().set_xlim(left=1)
plt.ylabel("y") 
plt.xlabel("x")
plt.title("Reference case") 
#plt.xlim([2,100])
plt.savefig("D:\\Google Drive\\Cpp\\SIMPLE\\velocity.png",bbox_inches='tight')
#plt.savefig("C:\\Users\\Niels\\Google Drive\\Cpp\\SIMPLE\\velocity.png",bbox_inches='tight')
#plt.legend(['c$_1$', 'c$_2$'])
#plt.legend(['CH$_4$', 'O$_2$', 'H$_2$', 'H$_2$O', 'CO', 'CO$_2$', 'C'])
#plt.legend(['DMC', 'MeCN'])
#plt.legend(['$\phi = 0.5$', '$\phi = 0.8$', '$\phi = 1$', '$\phi = 1.2$', '$\phi = 1.4$', '$\phi = 1.6$'])
#plt.legend(['Full rate', '1/10', '1/20', '1/40'], loc=1)
#plt.legend(['Steel', 'Aluminium'])
#plt.xticks([0,1,2,3,4,5,6,7,8,9])

#plt.axvline(x=1450, ls = '--', label='axvline - full height')
#plt.axvline(x=0.08, ls = '--', label='axvline - full height')

plt.show()

    
    
