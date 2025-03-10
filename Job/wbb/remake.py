with open('temp.txt', 'r+') as file:
    with open('new_text.txt', 'w') as file2:
        lines = file.readlines()
        for i in lines:
            i = '0x' + i
            file2.write(i)
