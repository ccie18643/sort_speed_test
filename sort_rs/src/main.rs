use std::fs::File;
use std::io::Read;
use std::time::Instant;
use std::env;


fn read_sample(filename: &String) -> Vec<u8> {

    let mut fd = File::open(&filename).expect("no file found");
    let metadata = File::metadata(&fd).expect("unable to read metadata");
    let mut buffer = vec![0; metadata.len() as usize];
    fd.read(&mut buffer).expect("buffer overflow");

    buffer
}


fn sort_bubble(sample: &mut Vec<u8>) -> u64 {

    let mut swapped = true;
    let sample_len = sample.len();
    let mut i;
    let mut comp_count = 0;
    let mut temp;

    while swapped {
        i = 0;
        swapped = false;
        while i < sample_len - 1 {
            if sample[i + 1] < sample[i] {
                temp = sample[i];
                sample[i] = sample[i + 1];
                sample[i + 1] = temp;
                swapped = true;
            }
            i += 1;
            comp_count += 1;
        }
    }
    comp_count
}


fn sort_selection(sample: &mut Vec<u8>) -> u64 {

    let sample_len = sample.len();
    let mut i;
    let mut sorted_len = 0;
    let mut comp_count = 0;
    let mut temp;

    while sorted_len < sample_len {
        i = sorted_len;
        while i < sample_len {
            if sample[i] < sample[sorted_len] {
                temp = sample[i];
                sample[i] = sample[sorted_len];
                sample[sorted_len] = temp;
            }
            i += 1;
            comp_count += 1;
        }
        sorted_len += 1;
    }
    comp_count
}


fn main(){

    let args: Vec<String> = env::args().collect();
    if args.len() < 2 {
        println!("Please specify algorithm [bubble|selection]");
        std::process::exit(-1);
    }

    if args.len() < 3 {
        println!("Please specify sample file");
        std::process::exit(-2);
    }

    let mut sample = read_sample(&args[2]);

    let comp_count;
    let time = Instant::now();

    if args[1] == "bubble" {
        comp_count = sort_bubble(&mut sample);
    }
    else if args[1] == "selection" {
        comp_count = sort_selection(&mut sample);
    }
    else {
        println!("Please specify algorithm [bubble|selection]");
        std::process::exit(-3);
    }

    let run_time = time.elapsed();

    if args.len() == 4 && args[3] == "result" {
        println!("{:?}", sample);
    }
    
    println!("language='rust', algorithm='{}', run_time={:?} comp_count={}", &args[1], run_time, comp_count);

    std::process::exit(0);
}

