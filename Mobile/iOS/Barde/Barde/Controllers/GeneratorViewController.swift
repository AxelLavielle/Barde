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
        
        let url = URL(string: "http://localhost")
        
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
        print(">>>", UserDefaults.standard.array(forKey: "styleArray") as Any)
        print(">>>", UserDefaults.standard.array(forKey: "chordsArray") as Any)
        print(">>>", UserDefaults.standard.array(forKey: "arpegiosArray") as Any)
        print(">>>", UserDefaults.standard.integer(forKey: "tempoValue") as Any)
        
        if player?.rate == 0
        {
            
            self.midiPlayer?.play({ () -> Void in
                print("finished")
                self.midiPlayer?.currentPosition = 0
            })
        
            setSessionPlayer()
            
            player!.play()
            let btnImage = UIImage(named: "icon-pause")
            controlButton.setImage(btnImage , for: UIControlState.normal)
            
            timer = Timer.scheduledTimer(timeInterval: 1.0, target: self, selector: #selector(updateCountdown), userInfo: nil, repeats: true)
            hasBeenPaused = false
            
            GeneratorManager.sharedInstance.sendData(arr: [0x2, 0x0, 0x0, 0x0, 0x12, 0x0, 0x0, 0x0])
        
        } else {
            
            if let player = self.midiPlayer {
                if player.isPlaying {
                    player.stop()
                }
            }
        
            player!.pause()
            let btnImage = UIImage(named: "icon-play")
            controlButton.setImage(btnImage , for: UIControlState.normal)
            
            timer.invalidate()
            hasBeenPaused = true
            
             GeneratorManager.sharedInstance.sendData(arr: [0x2, 0x0, 0x0, 0x0, 0x22, 0x0, 0x0, 0x0])
        }
    }
    
    @objc func updateCountdown() {
        if (!hasBeenPaused){
            intCounter += 1
            
            labelCurrentTime.text! = String(format: "%02d:%02d:%02d", intCounter / 3600, (intCounter % 3600) / 60, (intCounter % 3600) % 60)
        }
    }
    
    func setSessionPlayer() {
        let audioSession = AVAudioSession.sharedInstance()
        do {
            try audioSession.setCategory(AVAudioSessionCategoryPlayAndRecord, with: .mixWithOthers)
            try audioSession.setActive(true)
        } catch {
            print("couldn't set category \(error)")
        }
    }
    
    func createAVMIDIPlayerFromMIDIFIle() {
        
//        guard let midiFileURL = Bundle.main.url(forResource: nightBaldMountain, withExtension: "mid") else {
//            fatalError("\"nightBaldMountain.mid\" file not found.")
//        }
//
        let midiFileURL = GeneratorManager.sharedInstance.getDocumentsDirectory().appendingPathComponent("test.mid")
        
        print(">>B", midiFileURL)
        
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
