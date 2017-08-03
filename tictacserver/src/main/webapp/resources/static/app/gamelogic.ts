enum CellState  {Closed = 1, Opened_X = 2, Opened_O = 3};
enum Player     {Player1 = 1, Player2 = 2};
export enum GameResult {Won, Tie, Continue};

export class PlayerAction {
    command: String;
    commandParameter: String;

    constructor(command: String, commandParameter: String) {
        this.command = command;
        this.commandParameter = commandParameter;
    }
}

export class GameLogic {

    fieldMatrix: CellState[][];
    player: Player;
    state: GameResult;
    
    private MaxSize: number;

    constructor() {
        this.MaxSize = 4;
        this.player = Player.Player1;
        this.fieldMatrix = [];
        for (let i=0; i<this.MaxSize; ++i) {
            this.fieldMatrix[i] = [];
            for (let j=0; j<this.MaxSize; ++j) {
                this.fieldMatrix[i][j] = CellState.Closed;
            }
        }
    }

    private checkBoard(token: CellState): GameResult {
        // check vertical matches
        for (var i = 0; i < this.MaxSize; i++) {
            var match = true;
            for (var j = 0; j < this.MaxSize && match; j++) {
                match = match && (this.fieldMatrix[j][i] == token);
            }
            if (match) { return GameResult.Won; }
        }
        // check horizontal matches
        for (var i = 0; i < this.MaxSize; i++) {
            var match = true;
            for (var j = 0; j < this.MaxSize && match; j++) {
                match = match && (this.fieldMatrix[i][j] == token);
            }
            if (match) { return GameResult.Won; }
        }
        //check diagonal
        var match: boolean = true;
        for (var i = 0, j = 0; i < this.MaxSize; i++, j++) {
            match = match && (this.fieldMatrix[i][j] == token);
        }
        if (match) { return GameResult.Won; }
        //check diagonal
        match = true;
        for (var i = 0, j = this.MaxSize-1; j >= 0; i++, j--) {
            match = match && (this.fieldMatrix[i][j] == token);
        }
        if (match) { return GameResult.Won; }
        // check if all cells have been used
        for (var i = 0; i < this.MaxSize; i++) {
            for (var j = 0; j < this.MaxSize; j++) {
                // if at least one is not yet opened we can continue
                if (this.fieldMatrix[i][j] == CellState.Closed) {
                    return GameResult.Continue;
                }
            }
        }
        return GameResult.Tie;
    }

    // return true if the game should be continued
    private checkGame() {
        var result: GameResult = this.checkBoard(this.playersToken(this.player));
        if (result == GameResult.Won) {
            console.log("Player " + this.player + " won!");
        } else if (result == GameResult.Continue) {
            this.switchPlayer();
        } else {
            console.log("Tie! Everyone did great. Try again");
        }
        this.state = result;
    }

    private switchPlayer() {
        this.player = this.player == Player.Player1 ? Player.Player2 : Player.Player1;
        //console.log("Now player: " +  this.player);
    }

    private playersToken(player: Player): CellState {
        return player == Player.Player1 ? CellState.Opened_X : CellState.Opened_O;
    }

    onLastPositionChanged(position: string) {
        console.log("onLastPositionChanged:" + position);
        if (position.length != 2) {
            console.log("Wrong position value: " + position.length + "!");
        } else {
            var row: number = Number(position.charAt(0));
            var col: number = Number(position.charAt(1));
            if ((row >= 0 && row < this.MaxSize) && 
                (col >= 0 && col < this.MaxSize)) {
                if (this.fieldMatrix[row][col] == CellState.Closed) {
                    this.fieldMatrix[row][col] = (this.player == Player.Player1 ? CellState.Opened_X
                                                                                : CellState.Opened_O);
                    //console.log("Now fieldMatrix["+row+"]["+col+"]: " +  this.fieldMatrix[row][col]);
                    this.checkGame();
                }
            }
        }
    }

    buttonColor(position: string): string {
        var row: number = Number(position.charAt(0));
        var col: number = Number(position.charAt(1));
        var state: CellState  = this.fieldMatrix[row][col];
        if (state == CellState.Opened_X) {
            return "url('resources/x.png')";
        } else if (state == CellState.Opened_O) {
            return "url('resources/o.png')";
        } else {
            return "url('resources/blue.png')";
        }
    }
}