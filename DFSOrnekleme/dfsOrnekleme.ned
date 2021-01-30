import ned.DelayChannel;

simple node
{
    @display("i=device/laptop");
    gates:
        inout gate[];
}
channel wired extends DelayChannel
{
    @display("ls=#4E9A06,2,s");
    delay = 100ms;
}
channel wireless extends DelayChannel
{
    @display("ls=#A40000,2,da");
    delay = 250ms;
}
network bfsTabanliNetwork
{
    @display("bgi=background/streetmap;bgb=481.65686,283.43198");
    submodules:
        node1: node {
            @display("p=76.92309,230.76926");
        }
        node2: node {
            @display("p=249.11246,230.76926");
        }
        node3: node {
            @display("p=424.2604,230.76926");
        }
        node4: node {
            @display("p=424.2604,56.80474");
        }
        node5: node {
            @display("p=249.11246,56.80474");
        }
        node6: node {
            @display("p=76.92309,56.80474");
        }
    connections:
        node6.gate++ <--> wired <--> node5.gate++;
        node5.gate++ <--> wired <--> node4.gate++;
        node6.gate++ <--> wired <--> node1.gate++;
        node5.gate++ <--> wired <--> node2.gate++;
        node5.gate++ <--> wired <--> node3.gate++;
        node6.gate++ <--> wired { @display("ls=#4E9A06,,s"); } <--> node2.gate++;
        node1.gate++ <--> wired <--> node2.gate++;
        node2.gate++ <--> wired <--> node3.gate++;
        node3.gate++ <--> wired <--> node4.gate++;
}

