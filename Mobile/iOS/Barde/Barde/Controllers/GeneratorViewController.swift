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

class GeneratorViewController: UIViewController {

    var player:AVPlayer!
    var playerItem:AVPlayerItem?
    var playButton:UIButton?
    @IBOutlet weak var controlButton: UIButton!
    @IBOutlet weak var labelCurrentTime: UILabel!
    var timer = Timer()
    var intCounter: Int = 0
    var hasBeenPaused = false

    override func viewDidLoad() {
        super.viewDidLoad()
        
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
        if player?.rate == 0
        {
            player!.play()
            //playButton!.setImage(UIImage(named: "player_control_pause_50px.png"), forState: UIControlState.Normal)
            //playButton!.setTitle("Pause", for: UIControlState.normal)
            
            let btnImage = UIImage(named: "icon-pause")
            controlButton.setImage(btnImage , for: UIControlState.normal)
            
            timer = Timer.scheduledTimer(timeInterval: 1.0, target: self, selector: #selector(updateCountdown), userInfo: nil, repeats: true)
            hasBeenPaused = false

        } else {
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
            
            //Set counter in UILabel
            labelCurrentTime.text! = String(format: "%02d:%02d:%02d", intCounter / 3600, (intCounter % 3600) / 60, (intCounter % 3600) % 60)
        }
    }
    
}
