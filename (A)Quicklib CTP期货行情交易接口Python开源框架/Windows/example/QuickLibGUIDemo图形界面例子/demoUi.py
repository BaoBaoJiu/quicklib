#1.���ļ������õ�Python�ļ�Ϊ��������
#2.���ļ������õĿ��ļ�Quicklib CTP�ڻ������ͽ��׿���ѭ ��ԴЭ��GPL v3
#�򵥵�˵���Ի���GPL v3Э���Դ���룬�����˻�����������Լ�ʹ�ã�����Ա�Դ��
#�����ڸÿ�Դ���룬�����������������Ʒ������ҵ��Ϊ��Ҳ���뿪Դ��

#Quciklib Python��ܺ͹�����ѭGPL v3Э�������
#��1��Quicklib CTP   �ڻ������
#��2��Quicklib CTP   �ڻ����׿�
#��3��Quicklib CTP2  A�������
#��4��Quicklib MOMģʽ  �����ʹܽ��׿�
#�����ڽ����ʹ�Ͷ��ϵͳ��MOMģʽ��ʵ��˽ļ����Ͷ�˵�ѡ�ο��ˣ���ͨ���Լ��ķ��ϵͳ����ʵ�̣�

#Quciklib Python��ܺ͹����ݲ���ѭ��ԴЭ�������
#��5��Quicklib ������⣨Ԥ������ء������ź����ݸ��ơ�����������������ã�

#��Quciklib��Դ���������׵ģ����õ�ԭʼ���߿϶��ģ���������http://www.quciklib.cn��վ�ϣ�
#������ڡ���Դ˵���͸�л.txt�����������ļ����ϸ��·���ÿһ���°汾��Quicklib���

#ԭʼ���ߣ�QQ 147423661 ��(���Ǹ�)
#�ٷ���վ��http://www.quicklib.cn
#�ٷ�QQȺ��5172183(1Ⱥ)��25884087(2Ⱥ)

# encoding: UTF-8

"""
���ļ��а������ǽ���ƽ̨���ϲ�UI���֣�
ͨ��ͼ�ν�������м������������������������ݸ��¡�

Monitor��Ҫ���������ݣ��в��ְ����������ܡ�
Widget��Ҫ���ڵ����������ܣ��в��ְ������ݼ�ء�
"""

from __future__ import division

import time
import sys
import shelve
from collections import OrderedDict

import sip
from PyQt4 import QtCore, QtGui

from eventEngine import *



########################################################################
class LogMonitor(QtGui.QTableWidget):
    """������ʾ��־"""
    signal = QtCore.pyqtSignal(type(Event()))

    #----------------------------------------------------------------------
    def __init__(self, eventEngine, parent=None):
        """Constructor"""
        super(LogMonitor, self).__init__(parent)
        self.__eventEngine = eventEngine

        self.initUi()
        self.registerEvent()

    #----------------------------------------------------------------------
    def initUi(self):
        """��ʼ������"""
        self.setWindowTitle(u'��־')

        self.setColumnCount(2)                     
        self.setHorizontalHeaderLabels([u'ʱ��', u'��־'])

        self.verticalHeader().setVisible(False)                 # �ر���ߵĴ�ֱ��ͷ
        self.setEditTriggers(QtGui.QTableWidget.NoEditTriggers) # ��Ϊ���ɱ༭״̬

        # �Զ������п�
        self.horizontalHeader().setResizeMode(0, QtGui.QHeaderView.ResizeToContents)
        self.horizontalHeader().setResizeMode(1, QtGui.QHeaderView.Stretch)        

    #----------------------------------------------------------------------
    def registerEvent(self):
        """ע���¼�����"""
        # Qtͼ�������GUI���±���ʹ��Signal/Slot���ƣ������п��ܵ��³������
        # ��������Ƚ�ͼ�θ��º�����ΪSlot�����ź���������
        # Ȼ���źŵĴ�������ע�ᵽ�¼�����������
        self.signal.connect(self.updateLog)
        self.__eventEngine.register(EVENT_LOG, self.signal.emit)

    #----------------------------------------------------------------------
    def updateLog(self, event):
        """������־"""
        # ��ȡ��ǰʱ�����־����
        t = time.strftime('%H:%M:%S',time.localtime(time.time()))   
        log = event.dict_['log']                                    

        # �ڱ�����Ϸ�����һ��
        self.insertRow(0)              

        # ������Ԫ��
        cellTime = QtGui.QTableWidgetItem(t)    
        cellLog = QtGui.QTableWidgetItem(log)

        # ����Ԫ�������
        self.setItem(0, 0, cellTime)            
        self.setItem(0, 1, cellLog)


########################################################################
class AccountMonitor(QtGui.QTableWidget):
    """������ʾ�˻�"""
    signal = QtCore.pyqtSignal(type(Event()))

    dictLabels = OrderedDict()
    dictLabels['AccountID'] = u'Ͷ�����˻�'
    dictLabels['PreBalance'] = u'���'
    dictLabels['Withdraw'] = u'����'
    dictLabels['Deposit'] = u'���'    
    dictLabels['FrozenCash'] = u'�����ʽ�'
    dictLabels['FrozenMargin'] = u'���ᱣ֤��'
    dictLabels['FrozenCommission'] = u'����������'
    dictLabels['Commission'] = u'������'
    dictLabels['CurrMargin'] = u'��ǰ��֤��'
    dictLabels['Available'] = u'�����ʽ�'
    dictLabels['WithdrawQuota'] = u'��ȡ�ʽ�'
    dictLabels['Balance'] = u'�˻��ʽ�'

    #----------------------------------------------------------------------
    def __init__(self, eventEngine, parent=None):
        """Constructor"""
        super(AccountMonitor, self).__init__(parent)
        self.__eventEngine = eventEngine

        self.dictAccount = {}	    # ���������˻���Ӧ�ĵ�Ԫ��

        self.initUi()
        self.registerEvent()

    #----------------------------------------------------------------------
    def initUi(self):
        """"""
        self.setWindowTitle(u'�˻�')

        self.setColumnCount(len(self.dictLabels))
        self.setHorizontalHeaderLabels(self.dictLabels.values())

        self.verticalHeader().setVisible(False)                 # �ر���ߵĴ�ֱ��ͷ
        self.setEditTriggers(QtGui.QTableWidget.NoEditTriggers) # ��Ϊ���ɱ༭״̬	

    #----------------------------------------------------------------------
    def registerEvent(self):
        """"""
        self.signal.connect(self.updateAccount)
        self.__eventEngine.register(EVENT_ACCOUNT, self.signal.emit)

    #----------------------------------------------------------------------
    def updateAccount(self, event):
        """"""
        data = event.dict_['data']
        accountid = data['AccountID']

        # ���֮ǰ�Ѿ��յ�������˻�������, ��ֱ�Ӹ���
        if accountid in self.dictAccount:
            d = self.dictAccount[accountid]

            for label, cell in d.items():
                cell.setText(str(data[label]))
        # ��������µ�һ�У�������
        else:
            self.insertRow(0)
            d = {}

            for col, label in enumerate(self.dictLabels.keys()):
                cell = QtGui.QTableWidgetItem(str(data[label]))
                self.setItem(0, col, cell)
                d[label] = cell

            self.dictAccount[accountid] = d


########################################################################
class TradeMonitor(QtGui.QTableWidget):
    """������ʾ�ɽ���¼"""
    signal = QtCore.pyqtSignal(type(Event()))

    dictLabels = OrderedDict()
    dictLabels['InstrumentID'] = u'��Լ����'
    dictLabels['ExchangeInstID'] = u'��������Լ����'
    dictLabels['ExchangeID'] = u'������'
    dictLabels['Direction'] = u'����'   
    dictLabels['OffsetFlag'] = u'��ƽ'
    dictLabels['TradeID'] = u'�ɽ����'
    dictLabels['TradeTime'] = u'�ɽ�ʱ��'
    dictLabels['Volume'] = u'����'
    dictLabels['Price'] = u'�۸�'
    dictLabels['OrderRef'] = u'������'
    dictLabels['OrderSysID'] = u'����ϵͳ��'

    dictDirection = {}
    dictDirection['0'] = u'��'
    dictDirection['1'] = u'��'
    dictDirection['2'] = u'ETF�깺'
    dictDirection['3'] = u'ETF���'
    dictDirection['4'] = u'ETF�ֽ����'
    dictDirection['5'] = u'ծȯ���'
    dictDirection['6'] = u'ծȯ����'
    dictDirection['7'] = u'���'
    dictDirection['8'] = u'ת�й�'
    dictDirection['9'] = u'�����˻����'
    dictDirection['A'] = u'����Ʒ����'
    dictDirection['B'] = u'����Ʒ����'
    dictDirection['C'] = u'����Ʒת��'
    dictDirection['D'] = u'����Ʒת��'
    dictDirection['E'] = u'��������'
    dictDirection['F'] = u'��������'
    dictDirection['G'] = u'��ȯ����'
    dictDirection['H'] = u'��ȯ��ȯ'
    dictDirection['I'] = u'ֱ�ӻ���'
    dictDirection['J'] = u'ֱ�ӻ�ȯ'
    dictDirection['K'] = u'��ȯ��ת'
    dictDirection['L'] = u'OF�깺'    
    dictDirection['M'] = u'OF���'
    dictDirection['N'] = u'SF���'
    dictDirection['O'] = u'SF�ϲ�'
    dictDirection['P'] = u'����'
    dictDirection['Q'] = u'֤ȯ����/�ⶳ'
    dictDirection['R'] = u'��Ȩ'      

    dictOffset = {}
    dictOffset['0'] = u'����'
    dictOffset['1'] = u'ƽ��'
    dictOffset['2'] = u'ǿƽ'
    dictOffset['3'] = u'ƽ��'
    dictOffset['4'] = u'ƽ��'
    dictOffset['5'] = u'ǿ��'
    dictOffset['6'] = u'����ǿƽ'

    #----------------------------------------------------------------------
    def __init__(self, eventEngine, parent=None):
        """Constructor"""
        super(TradeMonitor, self).__init__(parent)
        self.__eventEngine = eventEngine

        self.initUi()
        self.registerEvent()	

    #----------------------------------------------------------------------
    def initUi(self):
        """"""
        self.setWindowTitle(u'�ɽ�')

        self.setColumnCount(len(self.dictLabels))
        self.setHorizontalHeaderLabels(self.dictLabels.values())

        self.verticalHeader().setVisible(False)                 # �ر���ߵĴ�ֱ��ͷ
        self.setEditTriggers(QtGui.QTableWidget.NoEditTriggers) # ��Ϊ���ɱ༭״̬	

    #----------------------------------------------------------------------
    def registerEvent(self):
        """"""
        self.signal.connect(self.updateTrade)
        self.__eventEngine.register(EVENT_TRADE, self.signal.emit)

    #----------------------------------------------------------------------
    def updateTrade(self, event):
        """"""
        data = event.dict_['data']

        self.insertRow(0)

        for col, label in enumerate(self.dictLabels.keys()):
            if label == 'Direction':
                try:
                    value = self.dictDirection[data[label]]
                except KeyError:
                    value = u'δ֪����'
            elif label == 'OffsetFlag':
                try:
                    value = self.dictOffset[data[label]]
                except KeyError:
                    value = u'δ֪����'
            else:
                value = str(data[label])

            cell = QtGui.QTableWidgetItem(value)
            self.setItem(0, col, cell)


########################################################################
class PositionMonitor(QtGui.QTableWidget):
    """������ʾ�ֲ�"""
    signal = QtCore.pyqtSignal(type(Event()))

    dictLabels = OrderedDict()
    dictLabels['InstrumentID'] = u'��Լ����'
    dictLabels['PosiDirection'] = u'����'  
    dictLabels['Position'] = u'�ֲ�'
    dictLabels['LongFrozen'] = u'��ͷ����'
    dictLabels['ShortFrozen'] = u'��ͷ����'
    dictLabels['PositionCost'] = u'�ֲֳɱ�'
    dictLabels['OpenCost'] = u'���ֳɱ�'

    dictPosiDirection = {}
    dictPosiDirection['1'] = u'��'
    dictPosiDirection['2'] = u'��'
    dictPosiDirection['3'] = u'��'

    #----------------------------------------------------------------------
    def __init__(self, eventEngine, parent=None):
        """Constructor"""
        super(PositionMonitor, self).__init__(parent)
        self.__eventEngine = eventEngine

        self.dictPosition = {}	    # ��������ֲֶ�Ӧ�ĵ�Ԫ��

        self.initUi()
        self.registerEvent()

    #----------------------------------------------------------------------
    def initUi(self):
        """"""
        self.setWindowTitle(u'�ֲ�')

        self.setColumnCount(len(self.dictLabels))
        self.setHorizontalHeaderLabels(self.dictLabels.values())

        self.verticalHeader().setVisible(False)                 # �ر���ߵĴ�ֱ��ͷ
        self.setEditTriggers(QtGui.QTableWidget.NoEditTriggers) # ��Ϊ���ɱ༭״̬	

    #----------------------------------------------------------------------
    def registerEvent(self):
        """"""
        self.signal.connect(self.updatePosition)
        self.__eventEngine.register(EVENT_POSITION, self.signal.emit)

    #----------------------------------------------------------------------
    def updatePosition(self, event):
        """"""
        data = event.dict_['data']

        # ���˷���ֵΪ�յ����
        if data['InstrumentID']:
            posid = data['InstrumentID'] + '.' + data['PosiDirection']

            # ���֮ǰ�Ѿ��յ�������˻�������, ��ֱ�Ӹ���
            if posid in self.dictPosition:
                d = self.dictPosition[posid]

                for label, cell in d.items():
                    if label == 'PosiDirection':
                        try:
                            value = self.dictPosiDirection[data[label]]
                        except KeyError:
                            value = u'δ֪����'
                    else:
                        value = str(data[label])	
                    cell.setText(value)
            # ��������µ�һ�У�������
            else:
                self.insertRow(0)
                d = {}

                for col, label in enumerate(self.dictLabels.keys()):
                    if label == 'PosiDirection':
                        try:
                            value = self.dictPosiDirection[data[label]]
                        except KeyError:
                            value = u'δ֪����'
                    else:
                        value = str(data[label])
                    cell = QtGui.QTableWidgetItem(value)
                    self.setItem(0, col, cell)
                    d[label] = cell

                self.dictPosition[posid] = d


########################################################################
class OrderMonitor(QtGui.QTableWidget):
    """������ʾ���б���"""
    signal = QtCore.pyqtSignal(type(Event()))

    dictLabels = OrderedDict()
    dictLabels['OrderRef'] = u'������'
    dictLabels['OrderSysID'] = u'ϵͳ���'
    dictLabels['InstrumentID'] = u'��Լ����'
    dictLabels['ExchangeInstID'] = u'��������Լ����'   
    dictLabels['Direction'] = u'����'
    dictLabels['CombOffsetFlag'] = u'��ƽ'
    dictLabels['LimitPrice'] = u'�۸�'
    dictLabels['VolumeTotalOriginal'] = u'ί������'
    dictLabels['VolumeTraded'] = u'�ɽ�����'
    dictLabels['InsertTime'] = u'ί��ʱ��'
    dictLabels['CancelTime'] = u'����ʱ��'
    dictLabels['StatusMsg'] = u'״̬��Ϣ'

    dictDirection = {}
    dictDirection['0'] = u'��'
    dictDirection['1'] = u'��'
    dictDirection['2'] = u'ETF�깺'
    dictDirection['3'] = u'ETF���'
    dictDirection['4'] = u'ETF�ֽ����'
    dictDirection['5'] = u'ծȯ���'
    dictDirection['6'] = u'ծȯ����'
    dictDirection['7'] = u'���'
    dictDirection['8'] = u'ת�й�'
    dictDirection['9'] = u'�����˻����'
    dictDirection['A'] = u'����Ʒ����'
    dictDirection['B'] = u'����Ʒ����'
    dictDirection['C'] = u'����Ʒת��'
    dictDirection['D'] = u'����Ʒת��'
    dictDirection['E'] = u'��������'
    dictDirection['F'] = u'��������'
    dictDirection['G'] = u'��ȯ����'
    dictDirection['H'] = u'��ȯ��ȯ'
    dictDirection['I'] = u'ֱ�ӻ���'
    dictDirection['J'] = u'ֱ�ӻ�ȯ'
    dictDirection['K'] = u'��ȯ��ת'
    dictDirection['L'] = u'OF�깺'    
    dictDirection['M'] = u'OF���'
    dictDirection['N'] = u'SF���'
    dictDirection['O'] = u'SF�ϲ�'
    dictDirection['P'] = u'����'
    dictDirection['Q'] = u'֤ȯ����/�ⶳ'
    dictDirection['R'] = u'��Ȩ'          

    dictOffset = {}
    dictOffset['0'] = u'����'
    dictOffset['1'] = u'ƽ��'
    dictOffset['2'] = u'ǿƽ'
    dictOffset['3'] = u'ƽ��'
    dictOffset['4'] = u'ƽ��'
    dictOffset['5'] = u'ǿ��'
    dictOffset['6'] = u'����ǿƽ'    

    #----------------------------------------------------------------------
    def __init__(self, eventEngine, mainEngine, parent=None):
        """Constructor"""
        super(OrderMonitor, self).__init__(parent)
        self.__eventEngine = eventEngine
        self.__mainEngine = mainEngine

        self.dictOrder = {}	    # �������汨���Ŷ�Ӧ�ĵ�Ԫ�����
        self.dictOrderData = {}	    # �������汨������

        self.initUi()
        self.registerEvent()

    #----------------------------------------------------------------------
    def initUi(self):
        """"""
        self.setWindowTitle(u'����')

        self.setColumnCount(len(self.dictLabels))
        self.setHorizontalHeaderLabels(self.dictLabels.values())

        self.verticalHeader().setVisible(False)                 # �ر���ߵĴ�ֱ��ͷ
        self.setEditTriggers(QtGui.QTableWidget.NoEditTriggers) # ��Ϊ���ɱ༭״̬

    #----------------------------------------------------------------------
    def registerEvent(self):
        """"""
        self.signal.connect(self.updateOrder)
        self.__eventEngine.register(EVENT_ORDER, self.signal.emit)

        self.itemDoubleClicked.connect(self.cancelOrder)

    #----------------------------------------------------------------------
    def updateOrder(self, event):
        """"""
        data = event.dict_['data']
        orderref = data['OrderRef']

        self.dictOrderData[orderref] = data

        # ���֮ǰ�Ѿ��յ�������˻�������, ��ֱ�Ӹ���
        if orderref in self.dictOrder:
            d = self.dictOrder[orderref]

            for label, cell in d.items():
                if label == 'Direction':
                    try:
                        value = self.dictDirection[data[label]]
                    except KeyError:
                        value = u'δ֪����'
                elif label == 'CombOffsetFlag':
                    try:
                        value = self.dictOffset[data[label]]
                    except KeyError:
                        value = u'δ֪����'
                elif label == 'StatusMsg':
                    value = data[label].decode('gbk')
                else:
                    value = str(data[label])	

                cell.setText(value)
        # ��������µ�һ�У�������
        else:
            self.insertRow(0)
            d = {}

            for col, label in enumerate(self.dictLabels.keys()):
                if label == 'Direction':
                    try:
                        value = self.dictDirection[data[label]]
                    except KeyError:
                        value = u'δ֪����'
                elif label == 'CombOffsetFlag':
                    try:
                        value = self.dictOffset[data[label]]
                    except KeyError:
                        value = u'δ֪����'
                elif label == 'StatusMsg':
                    value = data[label].decode('gbk')		
                else:
                    value = str(data[label])		

                cell = QtGui.QTableWidgetItem(value)
                self.setItem(0, col, cell)
                d[label] = cell

                cell.orderref =	orderref    # ��̬�󶨱����ŵ���Ԫ����

            self.dictOrder[orderref] = d

    #----------------------------------------------------------------------
    def cancelOrder(self, cell):
        """˫������"""
        orderref = cell.orderref
        order = self.dictOrderData[orderref]

        # ����ǰ��鱨���Ƿ��Ѿ���������ȫ���ɽ�
        if not (order['OrderStatus'] == '0' or order['OrderStatus'] == '5'):
            self.__mainEngine.cancelOrder(order['InstrumentID'],
                                          order['ExchangeID'],
                                          orderref,
                                          order['FrontID'],
                                          order['SessionID'])

    #----------------------------------------------------------------------
    def cancelAll(self):
        """ȫ��"""
        for order in self.dictOrderData.values():
            if not (order['OrderStatus'] == '0' or order['OrderStatus'] == '5'):
                self.__mainEngine.cancelOrder(order['InstrumentID'],
                                              order['ExchangeID'],
                                              order['OrderRef'],
                                              order['FrontID'],
                                              order['SessionID'])	


########################################################################
class MarketDataMonitor(QtGui.QTableWidget):
    """������ʾ����"""
    signal = QtCore.pyqtSignal(type(Event()))

    dictLabels = OrderedDict()
    dictLabels['Name'] = u'��Լ����'
    dictLabels['InstrumentID'] = u'��Լ����'
    dictLabels['ExchangeInstID'] = u'��Լ����������'

    dictLabels['BidPrice1'] = u'��һ��'
    dictLabels['BidVolume1'] = u'��һ��'
    dictLabels['AskPrice1'] = u'��һ��'
    dictLabels['AskVolume1'] = u'��һ��'    

    dictLabels['LastPrice'] = u'���¼�'
    dictLabels['Volume'] = u'�ɽ���'

    dictLabels['UpdateTime'] = u'����ʱ��'


    #----------------------------------------------------------------------
    def __init__(self, eventEngine, mainEngine, parent=None):
        """Constructor"""
        super(MarketDataMonitor, self).__init__(parent)
        self.__eventEngine = eventEngine
        self.__mainEngine = mainEngine

        self.dictData = {}

        self.initUi()
        self.registerEvent()

    #----------------------------------------------------------------------
    def initUi(self):
        """"""
        self.setWindowTitle(u'����')

        self.setColumnCount(len(self.dictLabels))
        self.setHorizontalHeaderLabels(self.dictLabels.values())

        self.verticalHeader().setVisible(False)                 # �ر���ߵĴ�ֱ��ͷ
        self.setEditTriggers(QtGui.QTableWidget.NoEditTriggers) # ��Ϊ���ɱ༭״̬

    #----------------------------------------------------------------------
    def registerEvent(self):
        """"""
        self.signal.connect(self.updateData)
        self.__eventEngine.register(EVENT_MARKETDATA, self.signal.emit)

    #----------------------------------------------------------------------
    def updateData(self, event):
        """"""
        data = event.dict_['data']
        instrumentid = data['InstrumentID']

        # ���֮ǰ�Ѿ��յ�������˻�������, ��ֱ�Ӹ���
        if instrumentid in self.dictData:
            d = self.dictData[instrumentid]

            for label, cell in d.items():
                if label != 'Name':
                    value = str(data[label])	
                else:
                    value = self.getName(data['InstrumentID'])
                cell.setText(value)
        # ��������µ�һ�У�������
        else:
            row = self.rowCount()
            self.insertRow(row)
            d = {}

            for col, label in enumerate(self.dictLabels.keys()):
                if label != 'Name':
                    value = str(data[label])				    
                    cell = QtGui.QTableWidgetItem(value)
                    self.setItem(row, col, cell)
                    d[label] = cell
                else:
                    name = self.getName(data['InstrumentID'])			    
                    cell = QtGui.QTableWidgetItem(name)	
                    self.setItem(row, col, cell)
                    d[label] = cell

            self.dictData[instrumentid] = d

    #----------------------------------------------------------------------
    def getName(self, instrumentid):
        """��ȡ����"""
        instrument = self.__mainEngine.selectInstrument(instrumentid)
        if instrument:
            return instrument['InstrumentName'].decode('GBK')
        else:
            return ''


########################################################################
class LoginWidget(QtGui.QDialog):
    """��¼"""

    #----------------------------------------------------------------------
    def __init__(self, mainEngine, parent=None):
        """Constructor"""
        super(LoginWidget, self).__init__()
        self.__mainEngine = mainEngine

        self.initUi()
        self.loadData()

    #----------------------------------------------------------------------
    def initUi(self):
        """��ʼ������"""
        self.setWindowTitle(u'��¼')

        # �������
        labelUserID = QtGui.QLabel(u'�˺ţ�')
        labelPassword = QtGui.QLabel(u'���룺')
        labelMdAddress = QtGui.QLabel(u'�����������')
        labelTdAddress = QtGui.QLabel(u'���׷�������')
        labelBrokerID = QtGui.QLabel(u'�����̴���')

        self.editUserID = QtGui.QLineEdit()
        self.editPassword = QtGui.QLineEdit()
        self.editMdAddress = QtGui.QLineEdit()
        self.editTdAddress = QtGui.QLineEdit()
        self.editBrokerID = QtGui.QLineEdit()

        self.editUserID.setMinimumWidth(200)

        buttonLogin = QtGui.QPushButton(u'��¼')
        buttonCancel = QtGui.QPushButton(u'ȡ��')
        buttonLogin.clicked.connect(self.login)
        buttonCancel.clicked.connect(self.close)

        # ���ò���
        buttonHBox = QtGui.QHBoxLayout()
        buttonHBox.addStretch()
        buttonHBox.addWidget(buttonLogin)
        buttonHBox.addWidget(buttonCancel)

        grid = QtGui.QGridLayout()
        grid.addWidget(labelUserID, 0, 0)
        grid.addWidget(labelPassword, 1, 0)
        grid.addWidget(labelMdAddress, 2, 0)
        grid.addWidget(labelTdAddress, 3, 0)
        grid.addWidget(labelBrokerID, 4, 0)
        grid.addWidget(self.editUserID, 0, 1)
        grid.addWidget(self.editPassword, 1, 1)
        grid.addWidget(self.editMdAddress, 2, 1)
        grid.addWidget(self.editTdAddress, 3, 1)
        grid.addWidget(self.editBrokerID, 4, 1)
        grid.addLayout(buttonHBox, 5, 0, 1, 2)

        self.setLayout(grid)

    #----------------------------------------------------------------------
    def login(self):
        """��¼"""
        userid = str(self.editUserID.text())
        password = str(self.editPassword.text())
        mdAddress = str(self.editMdAddress.text())
        tdAddress = str(self.editTdAddress.text())
        brokerid = str(self.editBrokerID.text())

        self.__mainEngine.login(userid, password, brokerid, mdAddress, tdAddress)
        self.close()

    #----------------------------------------------------------------------
    def loadData(self):
        """��ȡ����"""
        f = shelve.open('setting.vn')

        try:
            setting = f['login']
            userid = setting['userid']
            password = setting['password']
            mdAddress = setting['mdAddress']
            tdAddress = setting['tdAddress']
            brokerid = setting['brokerid']

            self.editUserID.setText(userid)
            self.editPassword.setText(password)
            self.editMdAddress.setText(mdAddress)
            self.editTdAddress.setText(tdAddress)
            self.editBrokerID.setText(brokerid)
        except KeyError:
            pass

        f.close()

    #----------------------------------------------------------------------
    def saveData(self):
        """��������"""
        setting = {}
        setting['userid'] = str(self.editUserID.text())
        setting['password'] = str(self.editPassword.text())
        setting['mdAddress'] = str(self.editMdAddress.text())
        setting['tdAddress'] = str(self.editTdAddress.text())
        setting['brokerid'] = str(self.editBrokerID.text())

        f = shelve.open('setting.vn')
        f['login'] = setting
        f.close()	

    #----------------------------------------------------------------------
    def closeEvent(self, event):
        """�ر��¼�����"""
        # �����ڱ��ر�ʱ���ȱ����¼���ݣ��ٹر�
        self.saveData()
        event.accept()  	


########################################################################
class ControlWidget(QtGui.QWidget):
    """���ò�ѯ����"""

    #----------------------------------------------------------------------
    def __init__(self, mainEngine, parent=None):
        """Constructor"""
        super(ControlWidget, self).__init__()
        self.__mainEngine = mainEngine

        self.initUi()

    #----------------------------------------------------------------------
    def initUi(self):
        """"""
        self.setWindowTitle(u'����')

        buttonAccount = QtGui.QPushButton(u'��ѯ�˻�')
        buttonInvestor = QtGui.QPushButton(u'��ѯͶ����')
        buttonPosition = QtGui.QPushButton(u'��ѯ�ֲ�')

        buttonAccount.clicked.connect(self.__mainEngine.getAccount)
        buttonInvestor.clicked.connect(self.__mainEngine.getInvestor)
        buttonPosition.clicked.connect(self.__mainEngine.getPosition)

        hBox = QtGui.QHBoxLayout()
        hBox.addWidget(buttonAccount)
        hBox.addWidget(buttonInvestor)
        hBox.addWidget(buttonPosition)

        self.setLayout(hBox)


########################################################################
class TradingWidget(QtGui.QWidget):
    """����"""
    signal = QtCore.pyqtSignal(type(Event()))

    dictDirection = OrderedDict()
    dictDirection['0'] = u'��'
    dictDirection['1'] = u'��'  

    dictOffset = OrderedDict()
    dictOffset['0'] = u'����'
    dictOffset['1'] = u'ƽ��' 
    dictOffset['3'] = u'ƽ��'

    dictPriceType = OrderedDict()
    dictPriceType['1'] = u'�����'
    dictPriceType['2'] = u'�޼�'
    dictPriceType['3'] = u'���ż�'
    dictPriceType['4'] = u'���¼�'

    # ��ת�ֵ�
    dictDirectionReverse = {value:key for key,value in dictDirection.items()}
    dictOffsetReverse = {value:key for key, value in dictOffset.items()}
    dictPriceTypeReverse = {value:key for key, value in dictPriceType.items()}

    #----------------------------------------------------------------------
    def __init__(self, eventEngine, mainEngine, orderMonitor, parent=None):
        """Constructor"""
        super(TradingWidget, self).__init__()
        self.__eventEngine = eventEngine
        self.__mainEngine = mainEngine
        self.__orderMonitor = orderMonitor

        self.instrumentid = ''

        self.initUi()
        self.registerEvent()

    #----------------------------------------------------------------------
    def initUi(self):
        """��ʼ������"""
        self.setWindowTitle(u'����')

        # ��߲���
        labelID = QtGui.QLabel(u'����')
        labelName =  QtGui.QLabel(u'����')
        labelDirection = QtGui.QLabel(u'ί������')
        labelOffset = QtGui.QLabel(u'��ƽ')
        labelPrice = QtGui.QLabel(u'�۸�')
        labelVolume = QtGui.QLabel(u'����')
        labelPriceType = QtGui.QLabel(u'�۸�����')

        self.lineID = QtGui.QLineEdit()
        self.lineName = QtGui.QLineEdit()

        self.comboDirection = QtGui.QComboBox()
        self.comboDirection.addItems(self.dictDirection.values())

        self.comboOffset = QtGui.QComboBox()
        self.comboOffset.addItems(self.dictOffset.values())

        self.spinPrice = QtGui.QDoubleSpinBox()
        self.spinPrice.setDecimals(4)
        self.spinPrice.setMinimum(0)
        self.spinPrice.setMaximum(10000)

        self.spinVolume = QtGui.QSpinBox()
        self.spinVolume.setMinimum(0)
        self.spinVolume.setMaximum(1000000)

        self.comboPriceType = QtGui.QComboBox()
        self.comboPriceType.addItems(self.dictPriceType.values())

        gridleft = QtGui.QGridLayout()
        gridleft.addWidget(labelID, 0, 0)
        gridleft.addWidget(labelName, 1, 0)
        gridleft.addWidget(labelDirection, 2, 0)
        gridleft.addWidget(labelOffset, 3, 0)
        gridleft.addWidget(labelPrice, 4, 0)
        gridleft.addWidget(labelVolume, 5, 0)
        gridleft.addWidget(labelPriceType, 6, 0)
        gridleft.addWidget(self.lineID, 0, 1)
        gridleft.addWidget(self.lineName, 1, 1)
        gridleft.addWidget(self.comboDirection, 2, 1)
        gridleft.addWidget(self.comboOffset, 3, 1)
        gridleft.addWidget(self.spinPrice, 4, 1)
        gridleft.addWidget(self.spinVolume, 5, 1)
        gridleft.addWidget(self.comboPriceType, 6, 1)	

        # �ұ߲���
        labelBid1 = QtGui.QLabel(u'��һ')
        labelBid2 = QtGui.QLabel(u'���')
        labelBid3 = QtGui.QLabel(u'����')
        labelBid4 = QtGui.QLabel(u'����')
        labelBid5 = QtGui.QLabel(u'����')

        labelAsk1 = QtGui.QLabel(u'��һ')
        labelAsk2 = QtGui.QLabel(u'����')
        labelAsk3 = QtGui.QLabel(u'����')
        labelAsk4 = QtGui.QLabel(u'����')
        labelAsk5 = QtGui.QLabel(u'����')

        self.labelBidPrice1 = QtGui.QLabel()
        self.labelBidPrice2 = QtGui.QLabel()
        self.labelBidPrice3 = QtGui.QLabel()
        self.labelBidPrice4 = QtGui.QLabel()
        self.labelBidPrice5 = QtGui.QLabel()
        self.labelBidVolume1 = QtGui.QLabel()
        self.labelBidVolume2 = QtGui.QLabel()
        self.labelBidVolume3 = QtGui.QLabel()
        self.labelBidVolume4 = QtGui.QLabel()
        self.labelBidVolume5 = QtGui.QLabel()	

        self.labelAskPrice1 = QtGui.QLabel()
        self.labelAskPrice2 = QtGui.QLabel()
        self.labelAskPrice3 = QtGui.QLabel()
        self.labelAskPrice4 = QtGui.QLabel()
        self.labelAskPrice5 = QtGui.QLabel()
        self.labelAskVolume1 = QtGui.QLabel()
        self.labelAskVolume2 = QtGui.QLabel()
        self.labelAskVolume3 = QtGui.QLabel()
        self.labelAskVolume4 = QtGui.QLabel()
        self.labelAskVolume5 = QtGui.QLabel()	

        labelLast = QtGui.QLabel(u'����')
        self.labelLastPrice = QtGui.QLabel()
        self.labelReturn = QtGui.QLabel()

        self.labelLastPrice.setMinimumWidth(60)
        self.labelReturn.setMinimumWidth(60)

        gridRight = QtGui.QGridLayout()
        gridRight.addWidget(labelAsk5, 0, 0)
        gridRight.addWidget(labelAsk4, 1, 0)
        gridRight.addWidget(labelAsk3, 2, 0)
        gridRight.addWidget(labelAsk2, 3, 0)
        gridRight.addWidget(labelAsk1, 4, 0)
        gridRight.addWidget(labelLast, 5, 0)
        gridRight.addWidget(labelBid1, 6, 0)
        gridRight.addWidget(labelBid2, 7, 0)
        gridRight.addWidget(labelBid3, 8, 0)
        gridRight.addWidget(labelBid4, 9, 0)
        gridRight.addWidget(labelBid5, 10, 0)

        gridRight.addWidget(self.labelAskPrice5, 0, 1)
        gridRight.addWidget(self.labelAskPrice4, 1, 1)
        gridRight.addWidget(self.labelAskPrice3, 2, 1)
        gridRight.addWidget(self.labelAskPrice2, 3, 1)
        gridRight.addWidget(self.labelAskPrice1, 4, 1)
        gridRight.addWidget(self.labelLastPrice, 5, 1)
        gridRight.addWidget(self.labelBidPrice1, 6, 1)
        gridRight.addWidget(self.labelBidPrice2, 7, 1)
        gridRight.addWidget(self.labelBidPrice3, 8, 1)
        gridRight.addWidget(self.labelBidPrice4, 9, 1)
        gridRight.addWidget(self.labelBidPrice5, 10, 1)	

        gridRight.addWidget(self.labelAskVolume5, 0, 2)
        gridRight.addWidget(self.labelAskVolume4, 1, 2)
        gridRight.addWidget(self.labelAskVolume3, 2, 2)
        gridRight.addWidget(self.labelAskVolume2, 3, 2)
        gridRight.addWidget(self.labelAskVolume1, 4, 2)
        gridRight.addWidget(self.labelReturn, 5, 2)
        gridRight.addWidget(self.labelBidVolume1, 6, 2)
        gridRight.addWidget(self.labelBidVolume2, 7, 2)
        gridRight.addWidget(self.labelBidVolume3, 8, 2)
        gridRight.addWidget(self.labelBidVolume4, 9, 2)
        gridRight.addWidget(self.labelBidVolume5, 10, 2)

        # ������ť
        buttonSendOrder = QtGui.QPushButton(u'����')
        buttonCancelAll = QtGui.QPushButton(u'ȫ��')

        # ���ϲ���
        hbox = QtGui.QHBoxLayout()
        hbox.addLayout(gridleft)
        hbox.addLayout(gridRight)

        vbox = QtGui.QVBoxLayout()
        vbox.addLayout(hbox)
        vbox.addWidget(buttonSendOrder)
        vbox.addWidget(buttonCancelAll)

        self.setLayout(vbox)

        # ��������
        buttonSendOrder.clicked.connect(self.sendOrder)
        buttonCancelAll.clicked.connect(self.__orderMonitor.cancelAll)
        self.lineID.returnPressed.connect(self.updateID)

    #----------------------------------------------------------------------
    def updateID(self):
        """��Լ�仯"""
        instrumentid = str(self.lineID.text())

        # ��ȡ��Լ
        instrument = self.__mainEngine.selectInstrument(instrumentid)
        if instrument:
            self.lineName.setText(instrument['InstrumentName'].decode('GBK'))

            # ��ռ۸�����
            self.spinPrice.setValue(0)
            self.spinVolume.setValue(0)

            # ���������ʾ
            self.labelBidPrice1.setText('')
            self.labelBidPrice2.setText('')
            self.labelBidPrice3.setText('')
            self.labelBidPrice4.setText('')
            self.labelBidPrice5.setText('')
            self.labelBidVolume1.setText('')
            self.labelBidVolume2.setText('')
            self.labelBidVolume3.setText('')
            self.labelBidVolume4.setText('')
            self.labelBidVolume5.setText('')	
            self.labelAskPrice1.setText('')
            self.labelAskPrice2.setText('')
            self.labelAskPrice3.setText('')
            self.labelAskPrice4.setText('')
            self.labelAskPrice5.setText('')
            self.labelAskVolume1.setText('')
            self.labelAskVolume2.setText('')
            self.labelAskVolume3.setText('')
            self.labelAskVolume4.setText('')
            self.labelAskVolume5.setText('')
            self.labelLastPrice.setText('')
            self.labelReturn.setText('')

            # ����ע���¼�����
            self.__eventEngine.unregister(EVENT_MARKETDATA_CONTRACT+self.instrumentid, self.signal.emit)
            self.__eventEngine.register(EVENT_MARKETDATA_CONTRACT+instrumentid, self.signal.emit)

            # ���ĺ�Լ
            self.__mainEngine.subscribe(instrumentid, instrument['ExchangeID'])

            # ����Ŀǰ�ĺ�Լ
            self.instrumentid = instrumentid

    #----------------------------------------------------------------------
    def updateMarketData(self, event):
        """��������"""
        data = event.dict_['data']

        if data['InstrumentID'] == self.instrumentid:
            self.labelBidPrice1.setText(str(data['BidPrice1']))
            self.labelAskPrice1.setText(str(data['AskPrice1']))
            self.labelBidVolume1.setText(str(data['BidVolume1']))
            self.labelAskVolume1.setText(str(data['AskVolume1']))
            
            if data['BidVolume2']:
                self.labelBidPrice2.setText(str(data['BidPrice2']))
                self.labelBidPrice3.setText(str(data['BidPrice3']))
                self.labelBidPrice4.setText(str(data['BidPrice4']))
                self.labelBidPrice5.setText(str(data['BidPrice5']))

                self.labelAskPrice2.setText(str(data['AskPrice2']))
                self.labelAskPrice3.setText(str(data['AskPrice3']))
                self.labelAskPrice4.setText(str(data['AskPrice4']))
                self.labelAskPrice5.setText(str(data['AskPrice5']))
            
                self.labelBidVolume2.setText(str(data['BidVolume2']))
                self.labelBidVolume3.setText(str(data['BidVolume3']))
                self.labelBidVolume4.setText(str(data['BidVolume4']))
                self.labelBidVolume5.setText(str(data['BidVolume5']))
                
                self.labelAskVolume2.setText(str(data['AskVolume2']))
                self.labelAskVolume3.setText(str(data['AskVolume3']))
                self.labelAskVolume4.setText(str(data['AskVolume4']))
                self.labelAskVolume5.setText(str(data['AskVolume5']))	

            self.labelLastPrice.setText(str(data['LastPrice']))
            rt = (data['LastPrice']/data['PreClosePrice'])-1
            self.labelReturn.setText(('%.2f' %(rt*100))+'%')

    #----------------------------------------------------------------------
    def registerEvent(self):
        """ע���¼�����"""
        self.signal.connect(self.updateMarketData)

    #----------------------------------------------------------------------
    def sendOrder(self):
        """����"""
        instrumentid = str(self.lineID.text())

        instrument = self.__mainEngine.selectInstrument(instrumentid)
        if instrument:
            exchangeid = instrument['ExchangeID']
            direction = self.dictDirectionReverse[unicode(self.comboDirection.currentText())]
            offset = self.dictOffsetReverse[unicode(self.comboOffset.currentText())]
            price = float(self.spinPrice.value())
            volume = int(self.spinVolume.value())
            pricetype = self.dictPriceTypeReverse[unicode(self.comboPriceType.currentText())]
            self.__mainEngine.sendOrder(instrumentid, exchangeid, price, pricetype, volume ,direction, offset)


########################################################################
class AboutWidget(QtGui.QDialog):
    """��ʾ������Ϣ"""

    #----------------------------------------------------------------------
    def __init__(self, parent):
        """Constructor"""
        super(AboutWidget, self).__init__(parent)

        self.initUi()

    #----------------------------------------------------------------------
    def initUi(self):
        """"""
        self.setWindowTitle(u'����')

        text = u"""
            QuickLib Demo  

            ������ڣ�2016/6/24 

            ���ߣ�quicklib.cn

            License�����

            ��ҳ��quicklib.cn

            QQ����Ⱥ��5172183

            ��������

            ����ϵͳ��Windows 10 רҵ�� 64λ

            Python���а棺Python 2.7.6  32λ

            ͼ�ο⣺PyQt4 4.11.3 Py2.7-x32

            ���׽ӿڣ�CTP

            ����������WingIDE 5.1.18

            EXE�����p2exe (make_exe.bat)
            """

        label = QtGui.QLabel()
        label.setText(text)
        label.setMinimumWidth(450)

        vbox = QtGui.QVBoxLayout()
        vbox.addWidget(label)

        self.setLayout(vbox)


########################################################################
class MainWindow(QtGui.QMainWindow):
    """������"""
    signalInvestor = QtCore.pyqtSignal(type(Event()))
    signalLog = QtCore.pyqtSignal(type(Event()))

    #----------------------------------------------------------------------
    def __init__(self, eventEngine, mainEngine):
        """Constructor"""
        super(MainWindow, self).__init__()
        self.__eventEngine = eventEngine
        self.__mainEngine = mainEngine

        self.initUi()
        self.registerEvent()

    #----------------------------------------------------------------------
    def initUi(self):
        """"""
        # ��������
        self.setWindowTitle(u'��ӭʹ��QucikLib')

        # ��������
        self.logM = LogMonitor(self.__eventEngine, self)
        self.accountM = AccountMonitor(self.__eventEngine, self)
        self.positionM = PositionMonitor(self.__eventEngine, self)
        self.tradeM = TradeMonitor(self.__eventEngine, self)
        self.orderM = OrderMonitor(self.__eventEngine, self.__mainEngine, self)
        self.marketdataM = MarketDataMonitor(self.__eventEngine, self.__mainEngine, self)
        self.tradingW = TradingWidget(self.__eventEngine, self.__mainEngine, self.orderM, self)

        righttab = QtGui.QTabWidget()
        righttab.addTab(self.positionM, u'�ֲ�')
        righttab.addTab(self.accountM, u'�˻�')

        lefttab = QtGui.QTabWidget()
        lefttab.addTab(self.orderM, u'����')
        lefttab.addTab(self.tradeM, u'�ɽ�')
        lefttab.addTab(self.logM, u'��־')

        self.tradingW.setMaximumWidth(400)
        tradingVBox = QtGui.QVBoxLayout()
        tradingVBox.addWidget(self.tradingW)
        tradingVBox.addStretch()

        upHBox = QtGui.QHBoxLayout()
        upHBox.addLayout(tradingVBox)
        upHBox.addWidget(self.marketdataM)

        downHBox = QtGui.QHBoxLayout()
        downHBox.addWidget(lefttab)
        downHBox.addWidget(righttab)

        vBox = QtGui.QVBoxLayout()
        vBox.addLayout(upHBox)
        vBox.addLayout(downHBox)

        centralwidget = QtGui.QWidget()
        centralwidget.setLayout(vBox)
        self.setCentralWidget(centralwidget)

        # ����״̬��
        self.bar = self.statusBar()
        self.bar.showMessage(u'����Demo')

        # ���ò˵���
        actionLogin = QtGui.QAction(u'��¼', self)
        actionLogin.triggered.connect(self.openLoginWidget)
        actionExit = QtGui.QAction(u'�˳�', self)
        actionExit.triggered.connect(self.close)

        actionAbout = QtGui.QAction(u'����', self)
        actionAbout.triggered.connect(self.openAboutWidget)		

        menubar = self.menuBar()
        sysMenu = menubar.addMenu(u'ϵͳ')
        sysMenu.addAction(actionLogin)
        sysMenu.addAction(actionExit)

        helpMenu = menubar.addMenu(u'����')
        helpMenu.addAction(actionAbout)

    #----------------------------------------------------------------------
    def registerEvent(self):
        """"""
        self.signalInvestor.connect(self.updateInvestor)
        self.signalLog.connect(self.updateLog)

        self.__eventEngine.register(EVENT_INVESTOR, self.signalInvestor.emit)
        self.__eventEngine.register(EVENT_LOG, self.signalLog.emit)

    #----------------------------------------------------------------------
    def updateInvestor(self, event):
        """"""
        data = event.dict_['data']

        self.setWindowTitle(u'��ӭʹ��QuickLib���Demo  ' + data['InvestorName'].decode('GBK'))

    #----------------------------------------------------------------------
    def updateLog(self, event):
        """"""
        log = event.dict_['log']

        self.bar.showMessage(log)

    #----------------------------------------------------------------------
    def openLoginWidget(self):
        """�򿪵�¼"""
        try:
            self.loginW.show()
        except AttributeError:
            self.loginW = LoginWidget(self.__mainEngine, self)
            self.loginW.show()

    #----------------------------------------------------------------------
    def openAboutWidget(self):
        """�򿪹���"""
        try:
            self.aboutW.show()
        except AttributeError:
            self.aboutW = AboutWidget(self)
            self.aboutW.show()

    #----------------------------------------------------------------------
    def closeEvent(self, event):
        """�˳��¼�����"""
        reply = QtGui.QMessageBox.question(self, u'�˳�',
                                           u'ȷ���˳�?', QtGui.QMessageBox.Yes | 
                                           QtGui.QMessageBox.No, QtGui.QMessageBox.No)

        if reply == QtGui.QMessageBox.Yes:
            self.__mainEngine.exit()
            event.accept()
        else:
            event.ignore()       










