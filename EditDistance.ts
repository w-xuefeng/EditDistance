class EditDistance {
  public a: string = '';
  public b: string = '';
  constructor(a: string, b: string) {
    this.a = a;
    this.b = b;
  }
  private dis(a: string, b: string, i: number, j: number): number {
    if (i == 0) {
      return j;
    } else if (j == 0) {
      return i;
    } else if (i == 1 && j == 1) {
      return a.split('')[i] == b.split('')[j] ? 0 : 1;
    } else {
      return Math.min(
        Math.min(
          this.dis(a, b, i - 1, j - 1) +
            (a.split('')[i] == b.split('')[j] ? 0 : 1),
          this.dis(a, b, i, j - 1) + 1
        ),
        this.dis(a, b, i - 1, j) + 1
      );
    }
  }
  public getED(): number {
    return this.getMatrix()[this.a.length][this.b.length];
  }
  public getMatrix(): Array<Array<number>> {
    let Matrix: Array<Array<number>> = new Array();
    let i: number, j: number;
    for (i = 0; i <= this.b.length + 1; ++i) {
      Matrix[i] = new Array();
    }
    for (i = 0; i < this.a.length + 1; i++) {
      for (j = 0; j < this.b.length + 1; j++) {
        Matrix[i][j] = this.dis(this.a, this.b, i, j);
      }
    }
    return Matrix;
  }
}
