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

def main():
    from distutils.core import setup
    import py2exe
    #setup(windows = ['QuickLibDemo.pyw'])
    setup(windows=[{"script":"QuickLibGuiDemo.pyw", "icon_resources": [(1, "main.ico")]} ],options = { "py2exe":{"dll_excludes":["MSVCP90.dll"]}})
    #setup(console = ['QuickLibSimple.py'])
    #setup(
    #windows = [{"script":"QuickLibDemo.pyw", "icon_resources": [(1, "main.ico")]} ]
    #) 
    pass


 

if __name__ == '__main__':
    main()
