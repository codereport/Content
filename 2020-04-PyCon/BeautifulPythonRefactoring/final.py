# refactored: 
# https://towardsdatascience.com/web-scraping-html-tables-with-python-c9baba21059

import requests
import lxml.html as lh
import pandas as pd

url = 'http://pokemondb.net/pokedex/all'

#Create a handle, page, to handle the contents of the website
page = requests.get(url)

#Store the contents of the website under doc
doc = lh.fromstring(page.content)

#Parse data that are stored between <tr>..</tr> of HTML
tr_elements = doc.xpath('//tr')

col = [(t.text_content(), []) for t in tr_elements[0]]

for T in tr_elements[1:]:
    #Iterate through each element of the row
    for i, t in enumerate(T.iterchildren()):
        data = t.text_content() 
        #Convert any numerical value to integers
        try:
            data = int(data)
        except:
            pass
        #Append the data to the empty list of the i'th column
        col[i][1].append(data)

Dict = {title:column for (title,column) in col}
df   = pd.DataFrame(Dict)

print(df.head())
