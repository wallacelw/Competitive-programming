import os

directory = os.listdir(os.getcwd())

ignore = ['.git', 'Aux-Images', 'Aux-Notebook', 'README.md', 'notebookCreator.py']

with open(os.path.join(os.getcwd(),'Aux-Notebook/Notebook.md'), 'w', encoding='utf-8') as f:
    with open(os.path.join(os.getcwd(),'README.md'), 'r', encoding='utf-8') as read:
        for line in read.readlines():
            f.write(line )
    f.write('\n')
    for archive in sorted(directory):
        if archive in ignore:
            continue

        f.write('\n---\n\n')
        f.write('# ' + archive + "\n\n")

        subfiles = os.listdir(os.path.join(os.getcwd(), archive))
        
        for filename in sorted(subfiles):
            with open(os.path.join(os.getcwd(), archive, filename), 'r', encoding='utf-8') as file:
                lines = file.readlines()
                for i in lines:
                    f.write(i)
            f.write('\n\n')