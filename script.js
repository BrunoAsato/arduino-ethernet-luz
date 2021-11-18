function AlteraEstadoRele(){
    var estado = document.getElementById("estado").innerHTML;
    if(estado === "0"){
        document.getElementById("estado").innerHTML="1";
        document.getElementById("rele").innerHTML="<div class='circle rele_ligado'></div>";
        document.getElementById("botao").innerHTML="<a href='/?desligar' class='btn btn-warning'>Desligar Luz</a>";
    } else {
        document.getElementById("estado").innerHTML="0";
        document.getElementById("rele").innerHTML="<div class='circle rele_desligado'></div>";
        document.getElementById("botao").innerHTML="<a href='/?ligar' class='btn btn-success'>Ligar Luz</a>";
    }
}
 