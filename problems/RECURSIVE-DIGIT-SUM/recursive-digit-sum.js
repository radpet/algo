function sum(p){
    var result = 0;
    for(var i = 0;i < p.length;i++){
        result+=parseInt(p[i]);
   }
    return result;
}
function super_digit(p){
    if(p.length == 1){
      return p;
    }
    return super_digit(sum(p) + '');
}
function processData(input) {
    var arr = input.split(' ');
    var i = arr[0];
    var n = parseInt(arr[1]);
    var p = parseInt(super_digit(i))*n;

    console.log(super_digit(p+''));
}

process.stdin.resume();
process.stdin.setEncoding('ascii');
_input = '';
process.stdin.on('data', function (input) {
    _input += input;
});

process.stdin.on('end', function () {
   processData(_input);
});
