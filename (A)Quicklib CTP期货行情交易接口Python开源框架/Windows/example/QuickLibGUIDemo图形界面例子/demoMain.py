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

"""
���ļ��а������ǽ���ƽ̨����������
���ײ㡢�в㡢�ϲ�Ĺ��ܵ��룬�����С�
"""

import ctypes
import sys

from demoEngine import MainEngine
from demoUi import *

 


#----------------------------------------------------------------------
def main():
    """���������"""
    ctypes.windll.shell32.SetCurrentProcessExplicitAppUserModelID('QucikLib')  # win7������ע�͵�����   
    
    app = QtGui.QApplication(sys.argv)
    app.setWindowIcon(QtGui.QIcon('main.ico'))
    
    me = MainEngine()
    
    mw = MainWindow(me.ee, me)

 
 
 
    mw.setFixedSize(1000,620)  #���ô���̶���С 
 
  
    mw.showMaximized()
 
    #���ھ���
    mw.screen = QtGui.QDesktopWidget().screenGeometry()
    mw.size = mw.geometry()
    mw.move((mw.screen.width()-mw.size.width())/2, (mw.screen.height()-mw.size.height())/2)   
    mw.show()
    
    sys.exit(app.exec_())


if __name__ == '__main__':
    main()
    
