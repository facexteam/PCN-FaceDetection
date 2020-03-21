import os

def test(exe_path,file_list):
    with open(file_list,'r') as fout:
        lines=fout.readlines()
        for line in lines:
            line=line.strip()
            args=exe_path+" "+line
            p = os.popen(args, 'r')
            # while 1:
            #     line = p.readline();
            #     if '' == line:
            #         break
            #     print line
 
if __name__ == '__main__':
    exe_path='./test_pic'
    file_list='image_rects_list.txt'
    test(exe_path,file_list)

