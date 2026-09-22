    
<+$+> math;
<+$+> gameengine.name;
<+$+> sys;

i32 y <- 0;
i32 $p1 <- &y;
i32 $$p2 <- &p1;

y <- 1;

<-[]->{i32} list;
<-[]->{i32} list <- []{i32*2} -> {2,2};
<-[]->{i32} list1 <- []{i32*2};

// <-[]->{i32,i32} list2 <- []{[]{i32*2}*2} -> {{23,2},{23,23}};

<-[]->{} list12;
<-[]->{i32*2,i32*2} list3;
<-[]->{i32*2,i32*2} list3 <- []{{23,2},{23,23}};

?{y == 3 \/ x ==3} -> {
    y <- 9;
} -> ?{y == 2 /\ x==2} -> {
    y <- 3;
} -> {
    y <- 0;
}

<-@->{i32} name <- @{i32 x <- 0, i32 y <- 6} -> {
    ^^^ x + y; 
};

<=$=> <-@->{i32} print <- @{u8 *name};


<-@->{} fun1 <- @{} -> {
    y<-3;
    
    ^^^ ><;
    ^^^;
}

// funcion main call
i32 newvar <- name <| {2,4};

<-?->{ i32 i <- 0; i> 33; i++} -> {
    //code
}

<-?->{i32 i <- 0,i32 j <- 0; i>32; i++, j++} -> {

}

<-?->{;name != "artumus";} -> {
    //code  
}

{
    //code
} -> <-?->{;name!="artermus";}

<-:->{i32 value <-: list} -> {

}

<-<+>->{} user <- <+>{} -> {
    i32 name <- 32;
    i32 class <- 3;
    i32 play <- 32;
};

<-<|>->{} color <- <|>{} -> {
    up <- 3,
    down,
    right,
    left
};

<-<:>->{} player <- <:>{ class1, class2 } -> {
    <:+:>{u8 name, i32 money <- 0} -> {
        this.name = name; 
    }
    <-@->{} name <- @{i32 x<-0, i32 y <- 0} {
        ^ x+y;
    };
};

<-[]->{player*2,player*3} a <- []{
    {
        player <| {'2',34},
        player <| {'1', 34},
        player <| {'0', 32}
    },
    {
        player <| {'2',34},
        player <| {'1', 34},
        player <| {'0', 32}
    }
};

player p1 <- a <| {}
