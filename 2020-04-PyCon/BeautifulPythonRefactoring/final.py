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

col = []

for i, t in enumerate(tr_elements[0]):
    name = t.text_content()
    print('%d:"%s"'%(i, name))
    col.append((name, []))

#Since out first row is the header, data is stored on the second row onwards
for j in range(1, len(tr_elements)):
    #T is our j'th row
    T = tr_elements[j]

    #If row is not of size 10, the //tr data is not from our table 
    if len(T) != 10:
        break

    #i is the index of our column
    i = 0

    #Iterate through each element of the row
    for t in T.iterchildren():
        data = t.text_content() 
        #Check if row is empty
        if i > 0:
        #Convert any numerical value to integers
            try:
                data = int(data)
            except:
                pass
        #Append the data to the empty list of the i'th column
        col[i][1].append(data)
        #Increment i for the next column
        i += 1

Dict = {title:column for (title,column) in col}
df   = pd.DataFrame(Dict)

print(df.head())
