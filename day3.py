def task1(input, isFile=True):
  if (isFile):
    input = open(input)
  valid = 0
  for line in input:
    words = line.rstrip().split(' ')
    if isValid(words, 1):
      valid = valid + 1
  return valid

def isAnagram(words):
  sorted_words = []
  for word in words:
    sorted_words.append("".join(sorted(word)))
  print(sorted_words)
  return len(list(set(sorted_words))) == len(sorted_words)

def isValid(strings, task):
  ret = len(list(set(strings))) == len(strings)
  if (task==1):
    return ret
  return (ret and isAnagram(strings))

def task2(input, isFile=True):
  if (isFile):
    input = open(input)
  valid = 0
  for line in input:
    words = line.rstrip().split(' ')
    if isValid(words, 2):
      valid = valid + 1
  return valid

print("Task1\nNumber of valid Passphrases:", task1('/home/jakob/Skrivbord/input.txt'))
print("---\nTask2\nNumber of valid Passphrases:", task2('/home/jakob/Skrivbord/input.txt'))
