enum CellState {Closed = 1, Opened_X = 2, Opened_O = 3};
enum Player    {Player1, Player2};

export class GameLogic {

    fieldMatrix: CellState[][];
    player: Player;
    
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

    private checkGame() {
        
    }

    private switchPlayer() {
        this.player = this.player == Player.Player1 ? Player.Player2 : Player.Player1;
        //console.log("Now player: " +  this.player);
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
                    this.switchPlayer();
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