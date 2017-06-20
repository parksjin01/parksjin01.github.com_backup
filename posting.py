# -*- encoding: utf-8 -*-

import BeautifulSoup
import re
import os
import sys
reload(sys)
sys.setdefaultencoding('utf-8')

HTML = """<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Damotorie's World</title>
    <link href="./CSS/bootstrap.css" rel="stylesheet">
    <link href="./CSS/bootstrap-theme.css" rel="stylesheet">
    <link href="./JS/bootstrap.js" rel="script">
    <link href="./JS/npm.js" rel="script">
    <script>

    </script>
<body>
<nav class="navbar navbar-inverse navbar-fixed-top">
    <div class="container">
        <div class="navbar-header">
            <button type="button" class="navbar-toggle collapsed" data-toggle="collapse" data-target="#navbar" aria-expanded="false" aria-controls="navbar">
                <span class="sr-only">Toggle navigation</span>
                <span class="icon-bar"></span>
                <span class="icon-bar"></span>
                <span class="icon-bar"></span>
            </button>
            <a class="navbar-brand" href="#">Damotorie CTF's</a>
        </div>
        <div id="navbar" class="navbar-collapse collapse">
            <ul class="nav navbar-nav">
                <li><a href="#">Binary</a></li>
                <li><a href="#about">Reversing</a></li>
                <li><a href="#contact">ETC</a></li>
            </ul>
        </div><!--/.nav-collapse -->
    </div>
</nav>
<br>
<br>
<br>
<div class="container col-md-offset-2 col-md-8">
    <div>%s</div>
</div>
</body>
</html>"""
INDEX_FORM = """    <a href="/CTF/Binary/%s">
    <div class="col-md-offset-2 col-md-8"> <h3>%s</h3>
        <p>
            %s
        </p>
    </div>
    </a>"""
file_name = raw_input("Input your md file name with full path: ")
with open(file_name, 'rt') as f:
	md_file = f.read()

md_file = md_file.split('\n\n')
html_file = []
for sentence in md_file:
	tmp = re.sub(r"""(#{6}) ([\w!@#$%^&*()_\-{}[\]:";'<>?,./|\\=+]*)""", r'<h6>\2</h6>', sentence)
	tmp = re.sub(r"""(#{5}) ([\w!@#$%^&*()_\-{}[\]:";'<>?,./|\\=+]*)""", r'<h5>\2</h5>', tmp)
	tmp = re.sub(r"""(#{4}) ([\w!@#$%^&*()_\-{}[\]:";'<>?,./|\\=+]*)""", r'<h4>\2</h4>', tmp)
	tmp = re.sub(r"""(#{3}) ([\w!@#$%^&*()_\-{}[\]:";'<>?,./|\\=+]*)""", r'<h3>\2</h3>', tmp)
	tmp = re.sub(r"""(#{2}) ([\w!@#$%^&*()_\-{}[\]:";'<>?,./|\\=+]*)""", r'<h2>\2</h2>', tmp)
	tmp = re.sub(r"""(#{1}) ([\w!@#$%^&*()_\-{}[\]:";'<>?,./|\\=+]*)""", r'<h1>\2</h1>', tmp)
	tmp = re.sub(r"""(`{3})([\w\n!@#$%^&*()_\-{}[\]:";'<>?,./|\\=+]*)(`{3})""", r'<pre><code>\2</pre></code>', tmp)
	tmp = re.sub(r"""(`{1})([\w\n!@#$%^&*()_\-{}[\]:";'<>?,./|\\=+]*)(`{1})""", r'<code>\2</code>', tmp)
	html_file.append('<p>%s</p>' %tmp)

HTML = HTML %(''.join(html_file))
with open(file_name, 'wt') as f:
	f.write(HTML)
print file_name
os.rename(file_name, file_name.strip('.md')+'.html')
with open('./Binary.html', 'rt') as f:
	index = f.read()
index = index.split('<div class="container col-md-offset-2 col-md-8">')
soup = BeautifulSoup.BeautifulSoup(HTML)
cur_index = INDEX_FORM %(file_name.split('/')[-1].strip('.md')+'.html', soup.findAll('h2')[0].text, soup.findAll('p')[0].text)
print cur_index
index[1] = cur_index + index[1]
index = '<div class="container col-md-offset-2 col-md-8">'.join(index)
with open('./Binary.html', 'wt') as f:
	f.write(index)
