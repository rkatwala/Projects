import os
import sys
import re
import cx_Oracle

def get_text(filename):
    with open(filename, 'r') as f:
      text = f.read()
    return text

def get_synonyms(imuid):
    connection = cx_Oracle.connect("hl_www_dev", "hl_www_dev", "sfo-db01.healthline.com/devdb01")
    cursor = connection.cursor()
    cursor.execute("select STR from CONCEPT_SYNONYMS where concept_id = :1", [imuid])
    synonyms = []
    for row in cursor.fetchmany():
        synonym = row[0]
        synonyms.append(synonym)
    return synonyms

def get_regex_pattern(imuid):
    synonyms = get_synonyms(imuid)
    regex = '(' + '|'.join(synonyms) + ')'
    print(regex)
    return re.compile(regex, re.IGNORECASE)

def annotate(text, pattern):
    annotations = []
    for m in pattern.finditer(text):
        annotations.append([m.start(), m.end()])
    return annotations

def write_html(text, annotations, html_filename):
    with open(html_filename, 'w') as f:
        f.write('<html><body>')
        i = 0
        for annotation in annotations:
            start = annotation[0]
            end = annotation[1]
            if start > i:
                f.write(text[i:start].replace('\n', '<br>'))
            f.write('<font color="#CC0000">')
            f.write(text[start:end])
            f.write('</font')
            i = end
        if i < len(text):
            f.write(text[i:].replace('\n', '<br>'))
        f.write('</body></html>')

def main():
    imuid = int(sys.argv[1])
    filename = sys.argv[2]
    html_filename = filename[:-4] + '-' + str(imuid) + '.html'
    print(imuid, filename, html_filename)
    text = get_text(filename)
    # print(text)
    # print(imuid, get_synonyms(imuid))
    pattern = get_regex_pattern(imuid)
    annotations = annotate(text, pattern)
    write_html(text, annotations, html_filename)

if __name__ == '__main__':
    main()

