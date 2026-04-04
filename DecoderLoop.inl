template<typename Pushframe, typename GetFrame, typename ReturnFrame>
void FFmpeg::RunDecoderLoop(Pushframe pushframe, GetFrame getframe, ReturnFrame returnframe)
{
	printf("Decoder thread Runing!\n");
	AVPacket* Packet = av_packet_alloc();

	while (_DecodedThreadruning)
	{
		if (av_read_frame(_FormatContext, Packet) < 0)
		{
			// End Of File
			printf("Decoder thread stop!\n");
			break;
		}

		if (Packet->stream_index == _VideoStreamIndex)
		{
			avcodec_send_packet(_CodecContext, Packet);
			
			while (true)
			{
				printf("Tring to get a AVFrame\n");
				AVFrame* frame = getframe();
				printf("Got a frame\n");

				int ret = avcodec_receive_frame(_CodecContext, frame);

				if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
				{
					printf("EAGAIN\n");
					returnframe(frame);
					break;
				}
				else if (ret < 0)
				{
					printf("Decoder error!\n");
				}
				else if (ret == 0)
				{
					printf("Pushing Frame to Queue\n");
					pushframe(frame);
				}
			}

		}
		av_packet_unref(Packet);
	}
	av_packet_free(&Packet);
	printf("stop decoder\n");
}
