# Create a simulator object
set ns [new Simulator]

# Open the nam trace file
set nf [open out.nam w]
$ns namtrace-all $nf

# Open the event trace file
set nf1 [open out.tr w]
$ns trace-all $nf1

# Define a 'finish' procedure
proc finish { } {
    global ns nf nf1
    $ns flush-trace

    # Close the nam trace file
    close $nf

    # Close the event trace file
    close $nf1

    # Execute nam
    exec nam out.nam &
    exit 0
}

# Create two nodes
set n0 [$ns node]
set n1 [$ns node]

# Create a duplex link between the nodes
$ns duplex-link $n0 $n1 1Mb 10ms DropTail

# Create a UDP agent
set udp0 [new Agent/UDP]

# Attach UDP agent to node n0
$ns attach-agent $n0 $udp0

# Create a CBR traffic source and attach it to udp0
set cbr0 [new Application/Traffic/CBR]
$cbr0 set packetSize_ 500
$cbr0 set interval_ 0.005
$cbr0 attach-agent $udp0

# Create a Null agent (a traffic sink) and attach it to node n1
set null0 [new Agent/Null]
$ns attach-agent $n1 $null0

# Connect the traffic source with the traffic sink
$ns connect $udp0 $null0

# Schedule events for the CBR agent
$ns at 0.5 "$cbr0 start"
$ns at 4.5 "$cbr0 stop"

# Call the finish procedure after 5 seconds of simulation time
$ns at 5.0 "finish"

# Run the simulation
$ns run