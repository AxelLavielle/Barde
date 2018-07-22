//
//  GeneratorViewController.swift
//  Barde
//
//  Created by Arnaud Perrault on 26/05/2018.
//  Copyright © 2018 Arnaud Perrault. All rights reserved.
//

import Foundation
import UIKit
import AVKit
import Starscream

class GeneratorViewController: UIViewController {

    // this one is from a midi file
    var midiPlayer: AVMIDIPlayer?
    var soundbank: URL?
    let soundFontMuseCoreName = "GeneralUser GS MuseScore v1.442"
    let gMajor = "sibeliusGMajor"
    let nightBaldMountain = "ntbldmtn"
    
    var player:AVPlayer!
    var playerItem:AVPlayerItem?
    var playButton:UIButton?
    @IBOutlet weak var controlButton: UIButton!
    @IBOutlet weak var labelCurrentTime: UILabel!
    var timer = Timer()
    var intCounter: Int = 0
    var hasBeenPaused = false
    
    var styleViewController: StyleViewController?
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        createAVMIDIPlayerFromMIDIFIle()
        
        let url = URL(string: "http://cdn.nrjaudio.fm/audio1/fr/30001/mp3_128.mp3?origine=fluxradios")
        
        player = AVPlayer.init(url: url!)
        
        let playerLayer=AVPlayerLayer(player: player!)
        playerLayer.frame=CGRect(x:0, y:0, width:10, height:50)
        self.view.layer.addSublayer(playerLayer)
        
        let btnImage = UIImage(named: "icon-play")
        controlButton.setImage(btnImage , for: UIControlState.normal)
        controlButton.addTarget(self, action: #selector(GeneratorViewController.playButtonTapped(_:)), for: .touchUpInside)
        labelCurrentTime.text = "00:00:00"
    
    
    }
    
    @objc func playButtonTapped(_ sender:UIButton)
    {
        
        //
        
        let result =  SocketManager.sharedInstance.client.send(data: Data(bytes: [0x50]))
        
        print("AAAA", result)
       
        print(">>>", UserDefaults.standard.array(forKey: "styleArray"))
        print(">>>", UserDefaults.standard.array(forKey: "chordsArray"))
        print(">>>", UserDefaults.standard.array(forKey: "arpegiosArray"))
        print(">>>", UserDefaults.standard.integer(forKey: "tempoValue"))
        
        if player?.rate == 0
        {
            
            self.midiPlayer?.play({ () -> Void in
                print("finished")
                self.midiPlayer?.currentPosition = 0
            })
            
            
            player!.play()
            //playButton!.setImage(UIImage(named: "player_control_pause_50px.png"), forState: UIControlState.Normal)
            //playButton!.setTitle("Pause", for: UIControlState.normal)
            
            let btnImage = UIImage(named: "icon-pause")
            controlButton.setImage(btnImage , for: UIControlState.normal)
            
            timer = Timer.scheduledTimer(timeInterval: 1.0, target: self, selector: #selector(updateCountdown), userInfo: nil, repeats: true)
            hasBeenPaused = false
        } else {
            
            if let player = self.midiPlayer {
                if player.isPlaying {
                    player.stop()
                }
            }
        
            
            player!.pause()
            //playButton!.setImage(UIImage(named: "player_control_play_50px.png"), forState: UIControlState.Normal)
            //playButton!.setTitle("Play", for: UIControlState.normal)
            let btnImage = UIImage(named: "icon-play")
            controlButton.setImage(btnImage , for: UIControlState.normal)
            
            timer.invalidate()
            hasBeenPaused = true
        }
    }
    
    func secondsToHoursMinutesSeconds (seconds : Int) -> (Int, Int, Int) {
        return (seconds / 3600, (seconds % 3600) / 60, (seconds % 3600) % 60)
    }
    
    @objc func updateCountdown() {
        if (!hasBeenPaused){
            intCounter += 1
            
            labelCurrentTime.text! = String(format: "%02d:%02d:%02d", intCounter / 3600, (intCounter % 3600) / 60, (intCounter % 3600) % 60)
        }
    }
    
    func createAVMIDIPlayerFromMIDIFIle() {
        
        guard let midiFileURL = Bundle.main.url(forResource: nightBaldMountain, withExtension: "mid") else {
            fatalError("\"nightBaldMountain.mid\" file not found.")
        }
        //        guard let midiFileURL = Bundle.main.url(forResource: "sibeliusGMajor", withExtension: "mid") else {
        //            fatalError("\"sibeliusGMajor.mid\" file not found.")
        //        }
        
        guard let bankURL = Bundle.main.url(forResource: "GeneralUser GS MuseScore v1.442", withExtension: "sf2") else {
            fatalError("\"GeneralUser GS MuseScore v1.442.sf2\" file not found.")
        }
        
        do {
            try self.midiPlayer = AVMIDIPlayer(contentsOf: midiFileURL, soundBankURL: bankURL)
            print("created midi player with sound bank url \(bankURL)")
        } catch let error {
            print("Error \(error.localizedDescription)")
        }
        
        self.midiPlayer?.prepareToPlay()
    }
    
}
