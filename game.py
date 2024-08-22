# Game Settings
import os
# Turn 0, End | 1, Blue | 2, Red
turn = 1
gamerun = True
winner = "none"
gamedata = []

# Board Style
empty = '🔳 '
filled_blue = '🔵 '
filled_red = '🔴 '
numbers = ['1️⃣','2️⃣','3️⃣','4️⃣','5️⃣','6️⃣']
numbersallstr = '⏹  1️⃣  2️⃣  3️⃣  4️⃣  5️⃣  6️⃣'

#Blank Game Creation
for mm in range(0, 6):
    gamedata.append([])
    for m in range(0, 6):
        gamedata[mm].append(empty)

# fill (3, 3)
gamedata[2][2] = filled_blue
gamedata[2][3] = filled_red
gamedata[3][2] = filled_red
gamedata[3][3] = filled_blue



#Board Call function
def showBoard():

    showline = ''
#    os.system('cls' if os.name == 'nt' else 'clear')
    print(numbersallstr)
    
    # zip() was new for me :)
    for mm,counter in zip(gamedata, range(7)):
        showline = ' '
        for m in mm:
            showline += m
        print(numbers[counter], showline)

#Checking for Game end
def checkIfEnd():
    gameend = True
    
    for g in gamedata:
        for i in g:
            if i == empty:
                gameend = False
            
        return gameend
            
def checkForWinner():
    
    winner = "none" # optional line
    blue_count = 0
    red_count = 0
    
    for g in gamedata:
        for i in g:    
            if i == filled_blue:
                blue_count += 1
            elif i == filled_red:
                red_count += 1
        
    if red_count > blue_count:
        winner = "red"
    elif red_count < blue_count:
        winner = "blue"
        
        
    return winner

def placeBlueBlock():
    validmove = False
    
    while validmove == False:
        blue_move_row = int(input("""
            Blue's Turn |--
            Enter your Move (ROW) :
            """)) -1
        print('--|')
        
        blue_move_index = int(input("""
            Blue's Turn |--
            Enter your Move (Index) :
            """)) -1
        
        print('--|') 
        
        
        gamedata[blue_move_row][blue_move_index] = filled_blue
        columnSituation = []

        
        clear_spaced_gamedata = [[],[],[],[],[],]
        
        for i in gamedata:
                columnSituation.append(gamedata[gamedata.index(i)][blue_move_index])
                
        rowSituation = []
        for j in gamedata[blue_move_row]:
                rowSituation.append(j)
                
                
        # Right


        rowReplacements = rowSituation
        for z,index_counter_z in zip(rowSituation[blue_move_index + 1:], range(blue_move_index + 1, 7)):

            if z != filled_red:
                break
                
            
            if z == filled_red:
                rowReplacements[index_counter_z] = filled_blue
                if rowSituation[index_counter_z + 1] == filled_blue:
                    break
                if rowSituation[index_counter_z + 1] == empty:
                    break
        gamedata[blue_move_row] = rowReplacements
        print(rowReplacements)        
                
        #validmove = True

    
        #Left
        
        # (7 - tedad) - majhool = real index
        leftSide = rowSituation[:blue_move_index]
        reversedRowSituation_left = []
        for i in leftSide:
            reversedRowSituation_left.insert(0, i)
        
        
        tempRowReplacements = rowReplacements
        for og, ogLoopCounter in zip(reversedRowSituation_left, range(0, 6-blue_move_index)):
            
            if og == empty:
                break
            
            try:    
                if og == filled_red:
                    tempRowReplacements[(7 - len(reversedRowSituation_left)) - ogLoopCounter] = filled_blue
                    
            except IndexError:
                break
                    


            if og == filled_blue and ogLoopCounter > 0:
                rowReplacements = tempRowReplacements
            else:
                break
            
        print(reversedRowSituation_left)
        gamedata[blue_move_row] = rowReplacements
        validmove = True
            
                
                
                
        
        
        
        
'''
        for d,index_counter_d,real_index_d in zip(rowSituation[blue_move_index - 1::-1], range(-(blue_move_index) -1, -7), range(0, blue_move_index - 1)):
            print(d, index_counter_d)
            print(rowSituation[blue_move_index - 1::-1])
            if d != filled_red:
                break
                
            
            if d == filled_red:
                rowReplacements[index_counter_d] = filled_blue
                if rowSituation[index_counter_d - 1] == filled_blue:
                    break
                if rowSituation[index_counter_d - 1] == empty:
                    break
                
        
        '''
        
        
                    


        
        
        

def placeRedBlock():
    validmove = False
    
    while validmove == False:
        red_move_row = int(input("""
            Red's Turn |--
            Enter your Move (ROW) :
            """))
        print('--|')
        
        red_move_index = int(input("""
            Red's Turn |--
            Enter your Move (Index) :
            """))
        
        print('--|')
        if gamedata[red_move_row - 1][red_move_index - 1] == empty:
            gamedata[red_move_row - 1][red_move_index - 1] = filled_red
            validmove = True
        
        else:
            print('Invalid Move! You may only place blocks on empty slots.')
        
        
while gamerun == True:
    
    if checkIfEnd() == True: # END
        showBoard()
        print(checkForWinner(), 'won the game')
        gamerun = False
        
    if turn == 1: # BLUE
        showBoard()
        placeBlueBlock()
        showBoard()
        turn = 2
        
    if turn == 2: # RED
        showBoard()
        placeRedBlock()
        showBoard()
        turn = 1
