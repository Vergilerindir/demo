import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QWidget,QHBoxLayout,QVBoxLayout,QLabel, QLineEdit,QPushButton
from PyQt5.QtGui import QFont
from PyQt5.QtCore import QSize,Qt,QTimer, QTime,QThread, pyqtSignal

from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.figure import Figure

import serial
import struct
import numpy as np

READTICKPERIOD = 10000
#####################################################################
testlist = [0,1,2,3,4,5,6,7,8,9,10]
testlist0 = [11,12,13,14,15,16,17,18,19,20,21]
import random
#####################################################################
#####################################################################
window = 0
class graphUpdateThread(QThread):
    work_finished = pyqtSignal()  # Custom signal to indicate work is finished
    

    def run(self):
        global window
        window.readyHandle = 0
        window.line0.set_xdata(window.grafik_Zaman[:window.zaman])
        window.line0.set_ydata(window.grafik_Sicaklik[:window.zaman])
        window.line1.set_xdata(window.grafik_Zaman[:window.zaman])
        window.line1.set_ydata(window.grafik_Sicaklik_Rezistans[:window.zaman])

        window.canvas.draw()
        #print("q")
        self.work_finished.emit()  # Emit the signal when done






#####################################################################
#####################################################################

class MainWindow(QMainWindow):

    def __init__(self):
        super(MainWindow, self).__init__()
        self.hedef = 60
        self.setWindowTitle("FIRIN GOSTERGE")
        self.setFixedSize(QSize(1300,700))
        self.layout1 = QHBoxLayout()

        self.layout2 = QVBoxLayout()

        self.label_Sicaklik = QLabel()
        self.label_Sicaklik.setText("SICAKLIK")
        self.label_Sicaklik.setFont(QFont('Arial',96))
        self.label_Sicaklik.setFixedSize(QSize(650,150))
        self.label_Sicaklik.setAlignment(Qt.AlignCenter)    
        self.layout2.addWidget(self.label_Sicaklik)

        self.label_Sicaklik_Deger = QLabel()
        self.label_Sicaklik_Deger.setText("142")
        self.label_Sicaklik_Deger.setFixedSize(QSize(650,650))
        self.label_Sicaklik_Deger.setFont(QFont('Arial',135))
        self.label_Sicaklik_Deger.setAlignment(Qt.AlignCenter)
        self.layout2.addWidget(self.label_Sicaklik_Deger)
        self.layout1.addLayout(self.layout2)

        self.layout3 = QVBoxLayout()

         # Create a Matplotlib figure
        self.figure = Figure()
        self.canvas = FigureCanvas(self.figure)
        self.layout3.addWidget(self.canvas)
        self.zaman = 0

        #######################################
        self.grafik_Zaman = (1/6)*np.arange(500)
        self.grafik_Sicaklik = np.zeros(500)
        self.grafik_Sicaklik_Rezistans = np.zeros(500)
        self.grafik_hedef_UP = self.hedef*np.ones(500)*1.05
        self.grafik_hedef_DOWN = self.hedef*np.ones(500)*0.95
        self.grafik_Sicaklik[499] = 125


        # Create a Matplotlib axes  
        self.axes = self.figure.add_subplot(111)
        self.line0, = self.axes.plot(self.grafik_Zaman,self.grafik_Sicaklik,label = 'Temp Merkez')
        self.line0.set_linewidth(1)
        self.line1, = self.axes.plot(self.grafik_Zaman,self.grafik_Sicaklik_Rezistans,label = 'Temp Ust')
        self.line0.set_linewidth(1)

        self.lineUP = self.axes.plot(self.grafik_Zaman,self.grafik_hedef_UP,label = 'UST%5')
        self.lineDO = self.axes.plot(self.grafik_Zaman,self.grafik_hedef_DOWN,label = 'ALT%5')
        self.axes.set_xlabel('Zaman(Dakika)')
        self.axes.set_ylabel('Sıcaklık(Celisus)')
        self.axes.set_title("Sıcaklık Zaman Grafiği")  # Add a title to the axes.
        self.axes.legend()

        self.grafikThread = graphUpdateThread()
        self.grafikThread.work_finished.connect(self.graphUpdatedSign)



        
        self.layout4 = QHBoxLayout()
        self.label_Rezistans_Sicaklik =  QLabel()
        self.label_Rezistans_Sicaklik.setText("Rezistans Sicakligi")
        self.layout4.addWidget(self.label_Rezistans_Sicaklik)
        self.label_Rezistans_Sicaklik_Deger = QLabel() 
        self.label_Rezistans_Sicaklik_Deger.setText("42")
        self.layout4.addWidget(self.label_Rezistans_Sicaklik_Deger)
        self.layout3.addLayout(self.layout4)

        self.layout5 = QHBoxLayout()
        self.label_hedef_Sicaklik = QLabel()
        self.label_hedef_Sicaklik.setText("HEDEF SICAKLIK")
        self.layout5.addWidget(self.label_hedef_Sicaklik)

        self.label_hedef_Sicaklik_Deger = QLabel()
        self.label_hedef_Sicaklik_Deger.setText("80")
        self.layout5.addWidget(self.label_hedef_Sicaklik_Deger)
        
        self.buton_Set_Hedef_60 = QPushButton()
        self.buton_Set_Hedef_60.setText("60")
        self.buton_Set_Hedef_60.clicked.connect(self.buton60clicked)
        self.layout5.addWidget(self.buton_Set_Hedef_60)
        

        self.buton_Set_Hedef_70 = QPushButton()
        self.buton_Set_Hedef_70.setText("70")
        self.buton_Set_Hedef_70.clicked.connect(self.buton70clicked)
        self.layout5.addWidget(self.buton_Set_Hedef_70)

        self.layout3.addLayout(self.layout5)

        self.layout6 = QHBoxLayout()

        self.label_Zamanlayici = QLabel()
        self.label_Zamanlayici.setText("Zamanlayici (dakika)")
        self.layout6.addWidget(self.label_Zamanlayici)

        self.linin_Zamanlayici = QLineEdit()
        self.layout6.addWidget(self.linin_Zamanlayici)

        self.buton_Zamanlayici_Kur = QPushButton()
        self.buton_Zamanlayici_Kur.setText("Kur")
        self.buton_Zamanlayici_Kur.clicked.connect(self.sayacBaslat)
        self.layout6.addWidget(self.buton_Zamanlayici_Kur)

        self.layout3.addLayout(self.layout6)


        self.layout7 = QHBoxLayout()

        self.label_KalanSure = QLabel()
        self.label_KalanSure.setText("Kalan Sure")
        self.layout7.addWidget(self.label_KalanSure)

        self.label_KalanSure_Deger = QLabel()
        self.label_KalanSure_Deger.setText("00")
        self.layout7.addWidget(self.label_KalanSure_Deger)

        self.label_KalanSure_Birim= QLabel()
        self.label_KalanSure_Birim.setText("Dakika")
        self.layout7.addWidget(self.label_KalanSure_Birim)

        self.layout3.addLayout(self.layout7)
        


        self.layout8 = QHBoxLayout()

        self.linin_Com = QLineEdit()
        self.layout8.addWidget(self.linin_Com)

        self.buton_baglan = QPushButton()
        self.buton_baglan.setText("Baglan")
        self.buton_baglan.clicked.connect(self.buton_BaglanBasildi)
        self.layout8.addWidget(self.buton_baglan)

        self.buton_echo = QPushButton()
        self.buton_echo.setText("echo")
        self.buton_echo.clicked.connect(self.butonEchoClicked)
        self.layout8.addWidget(self.buton_echo)

        self.buton_durdur = QPushButton()
        self.buton_durdur.setText("durdur")
        self.buton_durdur.clicked.connect(self.butonDurdurClicked)
        self.layout8.addWidget(self.buton_durdur)

        self.layout3.addLayout(self.layout8)



        self.layout9 = QHBoxLayout()
        self.label_Durum = QLabel()
        self.label_Durum.setText("hareket yok")
        self.label_Durum.setAlignment(Qt.AlignCenter)
        self.layout9.addWidget(self.label_Durum)
        
        self.layout3.addLayout(self.layout9)


        self.layout1.addLayout(self.layout3)


        widget = QWidget()
        widget.setLayout(self.layout1)
        self.setCentralWidget(widget)

        self.geri_Sayac_Sayici = 0
        self.geri_Sayac = QTimer()

        self.warning_countDown = QTimer()
        self.warning_countDown.timeout.connect(self.warningTick)
        self.warning = 0
        
        
        self.geri_Sayac.timeout.connect(self.sayacTetikleme)

        self.seri_sayac = QTimer()
        self.seri_sayac.timeout.connect(self.seri_sayacBaslat)
        self.seri = 0
        self.output = 0
        self.outputM = 0
        self.outputR = 0
        self.test = 0
        self.readyHandle = 1
        self.usartOkundu = 1
    #def grafikGuncelle(self):
        #self.line0.set_xdata(self.grafik_Zaman[:self.zaman])
        #self.line0.set_ydata(self.grafik_Sicaklik[:self.zaman])
        #self.line1.set_xdata(self.grafik_Zaman[:self.zaman])
        #self.line1.set_ydata(self.grafik_Sicaklik_Rezistans[:self.zaman])
        #self.canvas.draw()
        #print("")
        
    def degerGuncelle(self):
        if self.zaman < 1000:
            self.grafik_Sicaklik[self.zaman] = self.output1
            self.grafik_Sicaklik_Rezistans[self.zaman] = self.output2
            self.zaman = self.zaman + 1
            if(self.readyHandle == 1):
                self.grafikThread.start()

        
        #print(np.size(self.grafik_Zaman))
        #print(np.size(self.grafik_Sicaklik))
        #print(np.size(self.grafik_Sicaklik_Rezistans))
        #self.grafikGuncelle()
    def sayacBaslat(self):
       self.geri_Sayac_Sayici = float(self.linin_Zamanlayici.text())*60
       self.geri_Sayac.start(1000)
       self.label_Durum.setText("Zamanlayıcı Ayarlandı")
    def sayacTetikleme(self):
        if (self.geri_Sayac_Sayici != 0):
            self.geri_Sayac_Sayici -= 1
            self.label_KalanSure_Deger.setText(str(round(self.geri_Sayac_Sayici/60,2)))
        else:
            self.geri_Sayac.stop()
            self.label_Durum.setText("Zamanlanlayıcı doldu")
            print("TEST VAL")
            self.butonDurdurClicked()
            print(self.test)
            
            
    def buton_BaglanBasildi(self):
        try:
            #print(self.linin_Com.text())
            
            self.seri = serial.Serial(self.linin_Com.text())
            self.label_Durum.setText("Bağlantı sağlandı.")
            self.buton_baglan.setEnabled(False)
            self.seri_sayac.start(1)
            
        except ValueError:
            self.label_Durum.setText("Hata: Haberleşme değişkenleri sınır dışında")
        except serial.SerialException:
            self.label_Durum.setText("Hata: Port isminin doğruluğundan emin olun")
    def seri_sayacBaslat(self):
        try:
            self.output = self.seri.read(20)
            self.seri_sayac.start(READTICKPERIOD)
            self.output1 = struct.unpack("f",self.output[0:4])
            self.output2 = struct.unpack("f",self.output[4:8])
            state = struct.unpack("i",self.output[8:12])
            eko = struct.unpack("i",self.output[12:16])
            hedef = struct.unpack("i",self.output[16:20])
            window.label_Sicaklik_Deger.setText(str(round(self.output1[0],2))) 
            window.label_Rezistans_Sicaklik_Deger.setText(str(round(self.output2[0],2)))
            self.label_hedef_Sicaklik_Deger.setText(str(hedef[0]))
            self.output1 = round(self.output1[0] ,2)
            self.output2 = round(self.output2[0] ,2)
            if(self.output1 < 60):
                self.warning = 0
                self.label_Sicaklik_Deger.setStyleSheet("background-color: white;")
                self.label_Durum.setStyleSheet("background-color: white;")
            if(self.output1 > 60 and self.warning == 0):
                self.warning = 1
                self.warning_countDown.start(175) 
            
            self.label_Durum.setText("Durum:"+ str(state[0]))

            if(eko[0] == 99):
                self.buton_echo.setStyleSheet("background-color: BLUE;")
            else:
                self.buton_echo.setStyleSheet("background-color: WHITE;")
            if(self.output1 > 300 or self.output1 < 0):
                self.label_Durum.setText("Uyarı anormal deger saptandı KONTROL EDIN")
                self.label_Durum.setStyleSheet("background-color: RED;")
            
                
            self.degerGuncelle()
        except:
            self.test += 1
            self.seri_sayac.start(250)
            self.label_Durum.setText("Seri Veri Okuma Başarısız. KONTROL EDIN")
            if(self.test % 2 == 0):
                self.label_Durum.setStyleSheet("background-color: red;")
                self.label_Sicaklik_Deger.setStyleSheet("background-color: white;")
            else:
                self.label_Durum.setStyleSheet("background-color: white;")
                self.label_Sicaklik_Deger.setStyleSheet("background-color: red;")
                

            
            
        

        
       
        
    def warningTick(self):
        if(self.warning != 0):
            self.warning_countDown.start(175)   
            self.label_Durum.setText("YÜKSEK SICAKLIK LÜTFEN SİSTEMİ YAKINDAN GÖZLEMLEYİN")
            if(self.warning % 2 == 0):
                self.label_Durum.setStyleSheet("background-color: red;")
                self.label_Sicaklik_Deger.setStyleSheet("background-color: white;")
            else:
                self.label_Durum.setStyleSheet("background-color: white;")
                self.label_Sicaklik_Deger.setStyleSheet("background-color: red;")
            self.warning += 1
            if(self.warning > 20000):
                self.warning = 1

    def graphUpdatedSign(self):
        self.readyHandle = 1
    def buton60clicked(self):
        self.seri.write(bytes('a','ascii'))
    def buton70clicked(self):
        self.seri.write(bytes('y','ascii'))
    def butonEchoClicked(self):
        self.seri.write(bytes('e','ascii'))
    def butonDurdurClicked(self):
        self.seri.write(bytes('d','ascii'))
app = QApplication(sys.argv)

window = MainWindow()
window.show()

app.exec()

print("qty")
