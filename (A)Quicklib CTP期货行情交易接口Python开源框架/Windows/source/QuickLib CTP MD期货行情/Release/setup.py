#1.���ļ������õ�Python�ļ�Ϊ��������
#2.���ļ������õĿ��ļ�Quicklib CTP�ڻ������ͽ��׿���ѭ ��ԴЭ��GPL v3
#Quciklib Python��ܺ͹�����ѭGPL v3Э�������
#��1��Quicklib CTP   �ڻ������
#��2��Quicklib CTP   �ڻ����׿�
#��3��Quicklib CTP2  A�������
#Quciklib Python��ܺ͹����ݲ���ѭ��ԴЭ�������
#��4��Quicklib ������⣨Ԥ������ء������ź����ݸ��ơ�����������������ã�
#ԭʼ���ߣ�QQ 147423661 ��(���Ǹ�)
#��Quciklib��Դ���������׵ģ����õ�ԭʼ���߿϶��ģ���������http://www.quciklib.cn��վ��
#�ٷ���վ��http://www.quicklib.cn
#�ٷ�QQȺ��5172183(1Ⱥ)��25884087(2Ⱥ)

def main():
    from distutils.core import setup
    import py2exe
    #setup(windows = ['QuickLibSimple.pyw'])
    #setup(console = ['QuickLibSimple.py'])
    setup(
    console = [{"script":"QuickLibDemo.py" ,"icon_resources": [(1, "main.ico")]} ]
    ) 
    
    #setup(console = [{"script": "QuickLibDemo.py"}])

    #
    pass

if __name__ == '__main__':
    main()
