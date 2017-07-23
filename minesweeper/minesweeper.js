var field = new Field(10,10)

function Cell(row, column) {
    this.row = row;
    this.column = column;
    this.bomb = false;
    this.open = false;
    this.siblings = -1;
}

Object.defineProperty(Cell.prototype,
                      "bomb",
                      { get: function() { return this.bomb },
                        set: function(bomb) { this.bomb = bomb }
                      })

function Field(rows, columns) {

    this.rowsCount = function() { return rows; }
    this.columnsCount = function() { return columns; }

    this.cells = new Array(rows)
    for (var i = 0; i < rows; ++i) {
        this.cells[i] = new Array(columns)
        for (var j = 0; j < columns; ++j) {
            this.cells[i][j] = new Cell(i,j)
        }
    }
}

Field.prototype.oneach = function(f, context) {
    for (var i = 0; i < this.rowsCount(); ++i) {
        for (var j = 0; j < this.columnsCount(); ++j) {
            f.call(context, this.cells[i][j])
        }
    }
}

Field.prototype.renderOn = function(canvas, width, height) {

    var cellWidth = width / this.columnsCount();
    var cellHeight = height / this.rowsCount();

    var self = this;
    (function renderMarkup() {
        var i;
        for (i = 0; i < self.columnsCount(); ++i) {
            canvas.beginPath();
            canvas.moveTo(i*cellWidth, 0);
            canvas.lineTo(i*cellWidth, height);
            canvas.stroke();
        }
        for (i = 0; i < self.rowsCount(); ++i) {
            canvas.beginPath();
            canvas.moveTo(0, i*cellHeight);
            canvas.lineTo(width, i*cellHeight);
            canvas.stroke();
        }
    }());

    var i,j;
    for (i = 0; i < this.columnsCount(); ++i) {
        for (j = 0; j < this.rowsCount(); ++j) {
            if (this.open) {

            } else {
                canvas.drawImage('qrc:/images/opened_button.png', i*cellWidth, j*cellHeight, cellWidth, cellHeight);
            }
        }
    }
}

function shuffle(field) {
    var max = 10;
    while(max) {
        var row = Math.round(Math.random()*100) % field.rowsCount();
        var column = Math.round(Math.random()*100) % field.columnsCount();
        if (max) {
            if (!field.cells[row][column].bomb) {
                field.cells[row][column].bomb = true;
                --max;
            }
        } else {
            return;
        }
    }
}

function inherit(p) {
    if (p == null) throw TypeError();
    if (Object.create)
        return Object.create(p);
    var t = typeof p;
    if (t !== "object" && t !== "function") throw TypeError();
    function f() {};
    f.prototype = p;
    return new f();
}

function prototypeInherit(o) {
    function F() {};
    F.prototype = o;
    return new F();
}

function extend(o, p) {
    for(prop in p) {
        o[prop] = p[prop];
    }
    return o;
}

function merge(o, p) {
    for(prop in p) {
        if (o.hasOwnProperty(prop)) continue;
        o[prop] = p[prop];
    }
    return o;
}

function restrict(o, p) {
    for (prop in o) {
        if (!(prop in p)) delete o[prop];
    }
    return o;
}

function subtract(o, p) {
    for(var prop in p) {
        delete o[prop];
    }
    return o;
}

function union(o,p) { return extend(extend({}, o), p) }

function intersection(o,p) { return restrict(extend({}, o), p) }

function keys(o) {
    if (typeof o !== "object") throw TypeError();
    var result = [];
    for(var prop in o) {
        if (o.hasOwnProperty(prop))
            result.push(prop);
    }
    return result;
}


